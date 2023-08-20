#include "stdafx.h"
#include "poltergeist_movement.h"
#include "poltergeist.h"
#include "../../../detail_path_manager.h"

void CPoltergeisMovementManager::move_along_path(
    CPHMovementControl* movement_control, Fvector& dest_position, float time_delta)
{
    if (!m_monster->is_hidden())
    {
        inherited::move_along_path(movement_control, dest_position, time_delta);
        return;
    }

    dest_position = m_monster->m_current_position;

    // Åñëè íåò äâèæåíèÿ ïî ïóòè
    if (!enabled() || path_completed() || detail().path().empty() ||
        detail().completed(m_monster->m_current_position, true) ||
        (detail().curr_travel_point_index() >= detail().path().size() - 1) || fis_zero(old_desirable_speed()))
    {
        m_speed = 0.f;
        dest_position = CalculateRealPosition();
        return;
    }

    if (time_delta < EPS)
    {
        dest_position = CalculateRealPosition();
        return;
    }

    // Âû÷èñëèòü ïðîéäåííóþ äèñòàíöèþ, îïðåäåëèòü öåëåâóþ ïîçèöèþ íà ìàðøðóòå,
    //			 èçìåíèòü detail().curr_travel_point_index()

    float desirable_speed = old_desirable_speed(); // æåëàåìàÿ ñêîðîñòü îáúåêòà
    float dist = desirable_speed * time_delta; // ïðîéäåííîå ðàññòîÿíèå â ñîîñòâåòñòâèå ñ æåëàåìîé ñêîðîñòüþ
    float desirable_dist = dist;

    // îïðåäåëèòü öåëåâóþ òî÷êó
    Fvector target;

    u32 prev_cur_point_index = detail().curr_travel_point_index();

    // îáíîâèòü detail().curr_travel_point_index() â ñîîòâåòñòâèå ñ òåêóùåé ïîçèöèåé
    while (detail().curr_travel_point_index() < detail().path().size() - 2)
    {
        float pos_dist_to_cur_point =
            dest_position.distance_to(detail().path()[detail().curr_travel_point_index()].position);
        float pos_dist_to_next_point =
            dest_position.distance_to(detail().path()[detail().curr_travel_point_index() + 1].position);
        float cur_point_dist_to_next_point = detail().path()[detail().curr_travel_point_index()].position.distance_to(
            detail().path()[detail().curr_travel_point_index() + 1].position);

        if ((pos_dist_to_cur_point > cur_point_dist_to_next_point) && (pos_dist_to_cur_point > pos_dist_to_next_point))
        {
            ++detail().m_current_travel_point;
        }
        else
            break;
    }

    target.set(detail().path()[detail().curr_travel_point_index() + 1].position);
    // îïðåäåëèòü íàïðàâëåíèå ê öåëåâîé òî÷êå
    Fvector dir_to_target;
    dir_to_target.sub(target, dest_position);

    // äèñòàíöèÿ äî öåëåâîé òî÷êè
    float dist_to_target = dir_to_target.magnitude();

    while (dist > dist_to_target)
    {
        dest_position.set(target);

        if (detail().curr_travel_point_index() + 1 >= detail().path().size())
            break;
        else
        {
            dist -= dist_to_target;
            ++detail().m_current_travel_point;
            if ((detail().curr_travel_point_index() + 1) >= detail().path().size())
                break;
            target.set(detail().path()[detail().curr_travel_point_index() + 1].position);
            dir_to_target.sub(target, dest_position);
            dist_to_target = dir_to_target.magnitude();
        }
    }

    if (prev_cur_point_index != detail().curr_travel_point_index())
        on_travel_point_change(prev_cur_point_index);

    if (dist_to_target < EPS_L)
    {
        detail().m_current_travel_point = detail().path().size() - 1;
        m_speed = 0.f;
        dest_position = CalculateRealPosition();
        return;
    }

    // óñòàíîâèòü ïîçèöèþ
    Fvector motion;
    motion.mul(dir_to_target, dist / dist_to_target);
    dest_position.add(motion);

    // óñòàíîâèòü ñêîðîñòü
    float real_motion = motion.magnitude() + desirable_dist - dist;
    float real_speed = real_motion / time_delta;

    m_speed = 0.5f * desirable_speed + 0.5f * real_speed;

    // Îáíîâèòü ïîçèöèþ
    m_monster->m_current_position = dest_position;
    m_monster->Position() = CalculateRealPosition();
    dest_position = m_monster->Position();
}

Fvector CPoltergeisMovementManager::CalculateRealPosition()
{
    Fvector ret_val = m_monster->m_current_position;
    ret_val.y += m_monster->m_height;
    return (ret_val);
}
