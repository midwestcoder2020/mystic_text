#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

class Utils{
    
    public:

        static std::vector<string> split_string(string data,char delim){

                std::vector<string> parts;
                string part_builder;

                for(int x = 0; x < data.size();x++){

                char t_c = data[x];

                if(t_c == delim){
                    parts.push_back(part_builder);
                    part_builder="";
                }
                else if(x==data.size()-1){
                    part_builder+=t_c;
                    parts.push_back(part_builder);
                }else{
                    part_builder+=t_c;
                }
                
            }

            return parts;
        }
};

class Display{


    public:

        Display(){

        } 

        void draw_menu(string title, string choice_1,string choice_2,string choice_3,string choice_4,string choice_5,string choice_7,string choice_6,string choice_8,string choice_9){
            printf("%s\n",title.c_str());

            printf("%s\n",choice_1.c_str());
            printf("%s\n",choice_2.c_str());
            printf("%s\n",choice_3.c_str());

            printf("%s\n",choice_4.c_str());
            printf("%s\n",choice_5.c_str());
            printf("%s\n",choice_6.c_str());

            printf("%s\n",choice_7.c_str());
            printf("%s\n",choice_8.c_str());
            printf("%s\n",choice_9.c_str());
        }

        void draw_text(string data){
            printf("%s\n",data.c_str());
        }

        void draw_text_f(string data, string data2){
            printf("%s%s\n",data.c_str(),data2.c_str());
        }

        void draw_text_g(string data){
            printf("%s\n\n",data.c_str());
        }

        void draw_inline_text(string data){
            printf("%s",data.c_str());
        }

        void draw_prompt(string data){
            printf("%s: \n",data.c_str());
        }

        void draw_cursor(){
            printf("> ");
        }
};

class Item{

    string name;

    string desc;

    bool can_equip;

    public:

        Item(string n,string d,bool can_e){
            name = n;
            desc = d;
            can_equip = can_e;
        }
        
        Item(){

        }

        string get_name(){
            return name;
        }

        string get_desc(){
            return desc;
        }

        bool equippable(){
            return can_equip;
        }

        void set_desc(string data){
            desc = data;
        }

        void set_name(string data){
            name = data;
        }
};

class Player{

    public:

        Item equipped_item;

        string name;

        int health;

        bool item_equipped;

        std::vector<Item> inventory;

        Player(string n){
            name = n;
            health = 100;
        }

        Player(){

        }

        bool equip_item(string item_name){
           bool res = false;
           //equip item if in inventory
            for(int x = 0; x < inventory.size();x++){
                if(strcmp(inventory.at(x).get_name().c_str(),item_name.c_str())==0){
                    equipped_item = inventory.at(x);
                    item_equipped = true;
                    res = true;    
                    break;
                }
           }

           return res;
       }



       string inspect_item(){
           //read description of item equipped
           if(item_equipped == true && equipped_item.get_name().size()> 0){
           string res = equipped_item.get_name();
           res += ' ';
           res += equipped_item.get_desc();
           return res;
           }else{
               return "no item equipped";
           }
       }

       void pickup_item(Item item){
           inventory.push_back(item);
       }

       Item get_curr_item(){
           return equipped_item;
       }

       int get_health(){
           return health;
       }

       void set_health(int i){
           health = i;
       }

       void use_item(){
           if(item_equipped){

           }
       }
};

class Location{

    public:

        string name;
        string status;
        string required_item;
        string progress_update;
        string unlock_text;
        bool has_item;
        bool locked;
        bool final_location;
        // std::<string> items;

        std::vector<Item> items;


        Location(string nam,string desc, std::vector<Item> its){
            name=nam;
            status= desc;
            items = its;

            if(its.size() > 0){
                has_item=false;
            }else{
                has_item=true;
            }

            locked=false;
        }

        Location(){

        }

        void remove_item(string i_name){
            for(int x = 0; x < items.size();x++){
                if(strcmp(items.at(x).get_name().c_str(),i_name.c_str())==0){
                        items.erase(items.begin()+x);
                }
            }
        }

        bool interact(string data){

            bool res = false;
            if(strcmp(data.c_str(),required_item.c_str())==0){

            }

            return res;
        }


};

class Game{


    public:

        Player player;

        Display display;

        Utils utils;

        int rooms_moved;

        int move_counter;

        int location_index;

        std::vector<string> state_updates;

        std::vector<Location> locations;

        std::vector<Item>items;

        std::unordered_map<string,Location> game_locs;

        bool game_over;

        std::vector<string> game_data_lines;

        int game_data_lines_count;

        int game_progress;

        string Title;
        
        string Intro;

        string Setting;

        string Objective;

        string player_input;

        string prev_loc_name;

        Location curr_loc;

        Game(){
            game_progress= -1;
        };

        string get_user_input(){
            string input;

            getline(cin,input);

            return input;
        }

        void init_game_data(){

            string temp_string;
            ifstream data_in("./data.txt");

            int its =0;

            while(true){

                getline(data_in,temp_string);

                if(temp_string.length()==0){
                    break;
                }

                game_data_lines.push_back(temp_string);
                its++;
                temp_string="";

            }


            game_data_lines_count = its;
            location_index = 0;

            
        };

        void extract_data(){

            string temp_line;
            
// 

            for(int x = 0; x < game_data_lines_count; x++){

                //extract title
                if(strcmp(game_data_lines.at(x).substr(0,5).c_str(),"title")==0){

                    Title = game_data_lines.at(x).substr(6,game_data_lines.at(x).size()-5);

                }


                //check if comment
                else if(strcmp(game_data_lines.at(x).substr(0,1).c_str(),"#")==0){
                    continue; 
                }
                
                //extract location
                else if(strcmp(game_data_lines.at(x).substr(0,8).c_str(),"location")==0){

                    std::vector<string> loc_string_parts;

                    std::vector<string> room_items;

                    string final_loc;
                    
                    temp_line=game_data_lines.at(x).substr(9,game_data_lines.at(x).size()-8);

                    loc_string_parts = utils.split_string(temp_line,'|');

                    string name = loc_string_parts.at(0);
                    string status= loc_string_parts.at(1);
                    string req_item = loc_string_parts.at(2);
                    string items = loc_string_parts.at(3);

                    string end_condition_room = loc_string_parts.at(4);

                    string update_text = loc_string_parts.at(5);

                    // //extract items
                    if(strcmp(items.c_str(),"none")==0){
                    }
                    else{
                    room_items= utils.split_string(items,'_');
                    }

                    Location loc;

                    loc.required_item = req_item;

                    for(int y = 0; y < room_items.size();y++){

                        
                        std::vector<string> item_parts = utils.split_string(room_items.at(y),'-'); 

                        Item item = Item();
                        
                        item.set_name(item_parts.at(0));
                        item.set_desc(item_parts.at(1));

                        loc.items.push_back(item);
                    }                    
                    loc.name=name;
                    loc.status = status;
                    loc.unlock_text = update_text;
                    if(strcmp(status.c_str(),"locked")==0){
                        loc.locked = true;
                    }

                    if(strcmp(end_condition_room.c_str(),"yes")==0){
                        loc.final_location = true;
                    }else{
                        loc.final_location = false;
                    }

                    game_locs[loc.name]=loc;

                    locations.push_back(loc);

                }

                //extract setting
                else if(strcmp(game_data_lines.at(x).substr(0,7).c_str(),"setting")==0){
                    Setting = game_data_lines.at(x).substr(8,game_data_lines.at(x).size()-7);

                }

                //extract objective
                else if(strcmp(game_data_lines.at(x).substr(0,9).c_str(),"objective")==0){
                    Objective = game_data_lines.at(x).substr(10,game_data_lines.at(x).size()-9);

                }

            }

            curr_loc = locations.at(location_index);
            
        };

        void init_items(){

        };

        void load_location(){
            curr_loc = locations.at(location_index);
        }

        void goto_location(string loc){

           for(int x = 0; x < locations.size();x++){

                if(strcmp(locations.at(x).name.c_str(),loc.c_str())==0){

                    if(curr_loc.locked == true && locations.at(x).locked == true){
                        display.draw_text("Something seems to be wrong...");
                        break;
                    }
                    else{
                    
                    if(abs(x-location_index)>1){
                        display.draw_text("Not possible..");
                    }else{
                    location_index = x;


                    }
                    break;
                    }
                }

            }
            
            curr_loc = locations.at(location_index);

        }

        //NOTE: change peek location to updated locked and unlocked room traversal
        void peek_loc(){
            if(curr_loc.locked == false && (location_index+1 < locations.size())){
                display.draw_text_f("You see ",locations.at(location_index+1).name.c_str());
            }else{
                display.draw_text_f("You see ",curr_loc.name.c_str());
            }
        }

        void examine_location(){

            if(curr_loc.locked == false){
                display.draw_text_f("You appear to be located within: ",curr_loc.name);
                display.draw_text("Here's whats laying around...");
                for(int x = 0; x < curr_loc.items.size();x++){
                    display.draw_text_f("Item: ",curr_loc.items.at(x).get_name());
                }
            }
            else{
                display.draw_text("Its locked...");
            }
        }
        
        bool pickup_item(string data){
            bool res = false;
            for(int x =0; x < curr_loc.items.size();x++){
                if(strcmp(data.c_str(),curr_loc.items.at(x).get_name().c_str())==0){
                    player.pickup_item(curr_loc.items.at(x));
                    curr_loc.remove_item(curr_loc.items.at(x).get_name());
                    res = true;
                    break;
                }   
            }

            return res;
        }

        void check_inventory(){
            display.draw_text("Your inventory:");
            for(int x = 0; x<player.inventory.size();x++){
                display.draw_text_f("Item: ",player.inventory.at(x).get_name());
            }
        } 

        void use_item(string data){


            
            //get name of current locations required item
            //check if they are the same
            if(strcmp(curr_loc.required_item.c_str(),data.c_str())==0){
                //if so unlock area and allow user to continue in location
                curr_loc.locked = false;
                display.draw_text(curr_loc.unlock_text);

            }
            else{
                display.draw_text("Nothing happened....");
            }
            

        }

        void update(){

            //get input
            player_input = get_user_input();
            
            string data = player_input;
            //handle user input updates
            //look around 
            if(strcmp(data.c_str(),"look around")==0){
                
                display.draw_text("looking around...");

                peek_loc();
            }

            else if(strcmp(data.c_str(),"inspect location")==0){

                display.draw_text("inspecting location");

                examine_location();
            }

            //goto location
            //look into better method to implement keys and items to enter/exit areas
            else if(strcmp(data.substr(0,4).c_str(),"goto")==0){

                string t_location = data.substr(5,data.size()-4);

                goto_location(t_location);

                display.draw_text_f("You are in ",curr_loc.name);
                
                
            }

            //check inventory
            else if(strcmp(data.c_str(),"check inventory")==0){
                display.draw_text_g("checking inventory...");
                check_inventory();
            }
            
            //pickup item
            else if(strcmp(data.substr(0,6).c_str(),"pickup")==0){
                string iname = data.substr(7,data.size()-6);
                bool res = pickup_item(iname);

                if(res){
                display.draw_text_f("you grabbed: ",iname);
                }
                
            }

            //inspect item
            else if(strcmp(data.c_str(),"inspect item")==0){
                string res = player.inspect_item();
                display.draw_text_f("you see a: ",res);
                
            }

            //equip item
            else if(strcmp(data.substr(0,5).c_str(),"equip")==0){
                string iname = data.substr(6,data.size()-5);

                cout << iname << endl;
                bool res = player.equip_item(iname);

                if(res){
                    display.draw_text_f("equipping ",iname);
                }else{
                    display.draw_text("Not possible...");
                }
            }

            //use item
            //need to fiture out how item will affect currnet location object
            //then trigger state updates for the room to player know they have
            //progressed

            else if(strcmp(data.c_str(),"use item")==0){

                string data = player.get_curr_item().get_name();

                use_item(data);
            }   

            //quit
            else if(strcmp(data.c_str(),"quit")==0){
                display.draw_text_g("good bye...");
                game_over=true;

            }else{
                printf("Hmmm. that doesn't seem right");
            }


            //end update from user input
            //check end condition
            if(curr_loc.final_location == true && curr_loc.locked == false){
                //display.draw_text(curr_loc.unlock_text);
                game_over=true;
            }
        }

        void render(){
                display.draw_menu("\nAlright. Whats next?","* - look around","* - inspect location","* - goto <location>","* - check inventory","* - pickup <item name>","* - inspect item","* - equip <item>","* - use item","* - quit");
                display.draw_cursor();
        }

        void get_player_name(){
            string t_name;

            printf("Welcome Player. Please enter your name: ");
            getline(cin,t_name);

            player = Player();
            player.name = t_name;

            printf("Ok %s it is. Good luck!\n",player.name.c_str());
        }

        //main loop
        void run(){

            init_game_data();

            extract_data();
            
            init_items();

            get_player_name();

            //display title screen
            display.draw_text(Title);

            //display level setting screen
            display.draw_text(Setting);

            //display objective
            display.draw_text(Objective);

            display.draw_text("Press any key to get started...");

            char _ = getchar();


            //loop
            while(!game_over){

                //display optiosn to user
                render();                

                //update
                update();

            }
        }
};

int main(int arc,char** argv){

    Game game = Game();

    game.run();

    return 0;
}

