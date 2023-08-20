#pragma once

class CEnergyHolder
{
    // ýíåðãèÿ
    float m_value; // òåêóùåå çíà÷åíèå ýíåðãèè
    float m_restore_vel; // ñêîðîñòü âîññòàíîâëåíèÿ (ltx-param)
    float m_decline_vel; // ñêîðîñòü óìåíüøåíèÿ ýíåðãèè â àêòèâíîì ñîñòîÿíèè (ltx-param)
    float m_critical_value; // êðèòè÷åñêîå çíà÷åíèå ýíåðãèè, ìåíüøå êîòîðîãî àêòèâíîñòü áóäåò îòêëþ÷åíà (ltx-param)
    float m_activate_value; // çíà÷åíèå ýíåðãèè, áîëüøå êîòîðîãî àêòèâíîñòü ìîæåò áûòü âîññòàíîâëåíà (ltx-param)
    u32 m_time_last_update; // âðåìÿ ïîñëåäíåãî îáíîâëåíèÿ ýíåðãèè
    float m_aggressive_restore_vel; // ñêîðîñòü àãðåññèâíîãî âîññòàíîâëåíèÿ (ltx-param)

    // àêòèâíîñòü
    bool m_active;

    // àâòîìàòè÷åñêàÿ àêòèâàöèÿ/äåàêòèâàöèÿ
    bool m_auto_activate;
    bool m_auto_deactivate;

    // îáíîâëåíå ýíåðãèè ðàçðåøåíî
    bool m_enable;

    // ñîñòîÿíèå àãðåññèâíîñòè
    bool m_aggressive;

public:
    CEnergyHolder();
    virtual ~CEnergyHolder();

    virtual void reinit();
    virtual void reload(LPCSTR section, LPCSTR prefix = "", LPCSTR suffix = "");

    virtual void schedule_update();

    virtual void on_activate(){};

    virtual void on_deactivate(){};

    // àêòèâíîñòü ïîëÿ
    void activate();
    void deactivate();
    IC bool is_active() { return m_active; }
    IC bool can_activate() { return (m_value > m_activate_value); }
    IC bool should_deactivate() { return (m_value < m_critical_value); }
    IC void set_auto_activate(bool b_auto = true) { m_auto_activate = b_auto; }
    IC void set_auto_deactivate(bool b_auto = true) { m_auto_deactivate = b_auto; }

    void enable();
    IC void disable() { m_enable = false; }

    IC void set_aggressive(bool b_val = true) { m_aggressive = b_val; }

    // DEBUG
    IC float get_value() { return m_value; }
};
