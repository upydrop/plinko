#ifndef IncludeParameters
#define IncludeParameters
#include "Dropdown.hpp"

class Parameters{
    private:
        int width = WIDTH/3;
        ALLEGRO_EVENT_QUEUE* queue = nullptr;
        vector<unique_ptr<Button>> riskLevels = {};
        unique_ptr<InputField> betInput = nullptr;
        unique_ptr<DropdownMenu> dropdownRows = nullptr;
        unique_ptr<Button> playB = nullptr;
        string selectedRisk = "low";
        ALLEGRO_COLOR bgcolor = al_map_rgb(26, 46, 57);
        ALLEGRO_COLOR bg_param_color = al_map_rgb(32, 54, 67);
        ALLEGRO_FONT* font = nullptr;
        unique_ptr<DropdownMenu> dropdownBCount = nullptr;
    public:
        Parameters();
        void event_update(int ball_count);
        void draw_update();
        InputField* get_betInput() const { return betInput.get(); };
        DropdownMenu* get_dropdownRows() const { return dropdownRows.get(); };
        DropdownMenu* get_dropdownBCount() const { return dropdownBCount.get(); };
        Button* get_playB() const { return playB.get(); }
        string get_selectedRisk() const {return selectedRisk; };
        virtual ~Parameters();
};

#endif