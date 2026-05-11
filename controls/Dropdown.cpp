#include "dropdown.hpp"

using namespace std;

DropdownMenu::DropdownMenu(float x, float y,
                           float width, float item_height,
                           const std::vector<std::string>& items,
                           const DropdownColors& colors)
    : x(x), y(y),
      width(width), item_height(item_height),
      m_items(items),
      m_selected(items.empty() ? -1 : 0),
      m_hovered(-1),
      m_open(false),
      m_colors(colors)
{}

DropdownColors DropdownMenu::default_colors(){
    DropdownColors c;
    c.selected_bg       = al_map_rgb(22, 36, 45);
    c.item_hover_bg     = al_map_rgb(43, 56, 65);
    c.item_hover_text   = al_map_rgb(255, 255, 255);
    c.border            = al_map_rgb(162, 162, 162);
    return c;
}


bool DropdownMenu::point_in_header(float mx, float my) const
{
    return mx >= x && mx <= x + width &&
           my >= y && my <= y + item_height;
}

int DropdownMenu::row_at(float mx, float my) const
{
    float list_top = y + item_height;
    float list_bot = list_top + item_height * m_items.size();
 
    if (mx < x || mx > x + width) return -1;
    if (my < list_top || my > list_bot)  return -1;
 
    int row = static_cast<int>((my - list_top) / item_height);
    if (row < 0 || row >= static_cast<int>(m_items.size())) return -1;
    return row;
}


void DropdownMenu::handle_event(const ALLEGRO_EVENT& ev){
    if (m_items.empty()) return;

    if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        float mx = static_cast<float>(ev.mouse.x);
        float my = static_cast<float>(ev.mouse.y);

        if (m_open)
            m_hovered = row_at(mx, my);
        else
            m_hovered = -1;
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        float mx = static_cast<float>(ev.mouse.x);
        float my = static_cast<float>(ev.mouse.y);

        if (!m_open)
        {
            if (point_in_header(mx, my))
                m_open = true;
        }
        else
        {
            int row = row_at(mx, my);
            if (row >= 0)
            {
                set_selected(row);
                m_open = false;
                m_hovered = -1;
            }
            else if (point_in_header(mx, my))
            {
                m_open = false;
                m_hovered = -1;
            }
            else
            {
                m_open = false;
                m_hovered = -1;
            }
        }
    }
}

void DropdownMenu::draw_header() const{
    al_draw_filled_rounded_rectangle(x,y,
                             x + width, y + item_height,
                             10, 10, m_colors.selected_bg);

    al_draw_rounded_rectangle(x, y,
                      x + width, y + item_height,
                      10, 10, m_colors.border, 1.0f);

    const std::string& label = (m_selected >= 0) ? m_items[m_selected] : m_items[0];
    if (m_font && !label.empty())
    {   
        int text_h = al_get_font_line_height(m_font);
        float text_y = y + (item_height - static_cast<float>(text_h)) * 0.5f;
        al_draw_text(m_font, m_colors.item_hover_text,
                     x + 8.0f, text_y,
                     ALLEGRO_ALIGN_LEFT, label.c_str());
    }

    if (m_font)
    {
        int text_h = al_get_font_line_height(m_font);
        float arrow_y = y + (item_height - static_cast<float>(text_h)) * 0.5f;
        al_draw_text(m_font, m_colors.item_hover_text,
                     x + width - 18.0f, arrow_y,
                     ALLEGRO_ALIGN_LEFT, m_open ? "^" : "v"); 
    }
}

void DropdownMenu::draw_list() const
{
    float list_top = y + item_height;
    int text_h = m_font ? al_get_font_line_height(m_font) : 0;

    for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
    {
        float row_y = list_top + static_cast<float>(i) * item_height;
        bool  hovered = (i == m_hovered);

        ALLEGRO_COLOR bg   = hovered ? m_colors.item_hover_bg   : m_colors.selected_bg;
        ALLEGRO_COLOR text = hovered ? m_colors.item_hover_text : m_colors.item_hover_text;

        al_draw_filled_rounded_rectangle(x, row_y,
                                         x + width, row_y + item_height,
                                         10, 10, bg);

        if (i != m_items.size()-1){
            al_draw_line(x, row_y + item_height,
                     x + width, row_y + item_height,
                     m_colors.border, 1.0f);
        }

        if (m_font)
        {
            float text_y = row_y + (item_height - static_cast<float>(text_h)) * 0.5f;
            al_draw_text(m_font, text,
                         x + 8.0f, text_y,
                         ALLEGRO_ALIGN_LEFT, m_items[i].c_str());
        }
    }

    al_draw_rounded_rectangle(x, list_top,
                      x + width, list_top + item_height * m_items.size(),
                      10, 10, m_colors.border, 1.0f);
}

void DropdownMenu::draw() 
{
    if (!m_font) m_font = al_create_builtin_font();
    draw_header();
    if (m_open)
        draw_list();
}

void DropdownMenu::set_selected(int index){
    if (index < 0 || index >= static_cast<int>(m_items.size())) return;
    if (index == m_selected) return;
    m_selected = index;
}

DropdownMenu::~DropdownMenu(){
    if (m_font) al_destroy_font(m_font);
}