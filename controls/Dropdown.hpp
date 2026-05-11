#ifndef IncludeDropdown
#define IncludeDropdown
#include "InputField.hpp"

struct DropdownColors
{
    ALLEGRO_COLOR selected_bg;   
    ALLEGRO_COLOR item_hover_bg;   
    ALLEGRO_COLOR item_hover_text;
    ALLEGRO_COLOR border;
};

class DropdownMenu
{
public:
    DropdownMenu(float x, float y,
                 float width, float item_height,
                 const vector<string>& items,
                 const DropdownColors& colors);

    ~DropdownMenu();

    void draw();

    const string& selected_item() const  { return m_items[m_selected]; }

    void handle_event(const ALLEGRO_EVENT& ev);

    void set_selected(int index);
    void close() { m_open = false; m_hovered = -1; }
    bool is_open() const { return m_open; }

    static DropdownColors default_colors();

private:
    float x, y;
    float width, item_height;

    vector<string> m_items;
    int  m_selected;
    int  m_hovered;
    bool m_open;

    ALLEGRO_FONT* m_font;
    DropdownColors m_colors;

    void  draw_header() const;
    void  draw_list() const;
    int   row_at(float mx, float my) const;
    bool  point_in_header(float mx, float my) const;
};

#endif