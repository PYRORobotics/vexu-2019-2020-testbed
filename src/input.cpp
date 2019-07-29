#include <stdio.h>
#include <stdlib.h>
#include "input.hpp"

pros::Controller Controller_1(pros::E_CONTROLLER_MASTER);
pros::Controller Controller_2(pros::E_CONTROLLER_MASTER);
Profile Active_Profile;

std::string action_list[]
{
  "Drive 1", // Action 1
  "Drive 2" // Action 2
};

std::map<controller_input, int> controller_1_values;
std::map<controller_input, int> controller_2_values;



void update_controller_values(void *)
{
  while(1){

  // Controller 1
  // Analog Joysticks
  controller_1_values[LX] = Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  controller_1_values[LY] = Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  controller_1_values[RX] = Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  controller_1_values[RY] = Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // Digital Buttons
  controller_1_values[A] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_A);
  controller_1_values[B] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  controller_1_values[X] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  controller_1_values[Y] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  controller_1_values[U] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  controller_1_values[D] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  controller_1_values[L] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  controller_1_values[R] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  controller_1_values[L1] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  controller_1_values[L2] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  controller_1_values[R1] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  controller_1_values[R2] = Controller_1.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  // Controller 2
  // Analog Joysticks
  controller_2_values[LX] = Controller_2.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  controller_2_values[LY] = Controller_2.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  controller_2_values[RX] = Controller_2.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  controller_2_values[RY] = Controller_2.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

  // Digital Buttons
  controller_2_values[A] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_A);
  controller_2_values[B] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  controller_2_values[X] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  controller_2_values[Y] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  controller_2_values[U] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  controller_2_values[D] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  controller_2_values[L] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  controller_2_values[R] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  controller_2_values[L1] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  controller_2_values[L2] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  controller_2_values[R1] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  controller_2_values[R2] = Controller_2.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  pros::delay(10);
}
}

void update_sensor_values(void *)
{

}

void Profile::set_layout(std::string profile_file_name)
{
  std::cout << "setting layout\n";
  std::string line;
  char filepath[1000];
  strcpy(filepath, "/usd/");
  strcat(filepath, profile_file_name.c_str());
  strcat(filepath, ".csv");
  std::cout << "Before open: File:" << filepath << "\n";
  FILE* profile_file = fopen(filepath, "r");
  std::string controller_num;
  std::string action;
  std::string value;
  std::pair<pros::Controller*, controller_input> ci;

  std::cout << "File:" << filepath << "\n";

  if (profile_file != NULL)  // same as: if (profile_file.good())
  {
    std::cout << "Found File\n";
    char *controller_numc = NULL;
    char *actionc = NULL;
    char *valuec = NULL;

    size_t len = 0;
    ssize_t read;

    int itt = 0;
    int last_action_len = 0;
    int last_value_len = 0;

    while ((read=__getdelim(&controller_numc,&len,',',profile_file))!= -1)//(profile_file, controller_num, ','))
    {

      //std::cout << "===================Start Itteration " << (itt + 1) <<"==================\n";
      std::cout << "Found Line: " << controller_numc;
      //cout << "ID: " << ID << " " ;

      __getdelim(&valuec,&len,',',profile_file);
      //cout << "Sexo: " <<  genero<< " "  ;
      std::cout << valuec << "\n";

      __getline(&actionc,&len,profile_file);
      std::cout << actionc;
      std::cout << ", ";

      controller_num.assign(controller_numc);
      action.assign(actionc);
      value.assign(valuec);







      if(!value.empty())
      {


        controller_num = controller_num.substr(0, 12);
        action = action.substr(0, action.length()-1);
        value = value.substr(0, value.length()-1);
        //std::cout << "Controller_num: " << controller_num << "\n";
        //std::cout << "value: " << value << "\n";
        //std::cout << "action: " << action << "\n";


        //std::cout << " Cont 1 comp: " << controller_num.compare("Controller 1");
        if(controller_num.compare("Controller 1") == 0)
        {
          //std::cout << "Controller 1 Selected!\n";
          //std::cout << value << "\n";
          //std::cout << "Value: " << value << " End value\n";

          if(value.compare("LX") == 0)      ci = std::make_pair(&Controller_1,LX);
          else if(value.compare("LY") == 0) ci = std::make_pair(&Controller_1,LY);
          else if(value.compare("RX") == 0) ci = std::make_pair(&Controller_1,RX);
          else if(value.compare("RY") == 0) ci = std::make_pair(&Controller_1,RY);
          else if(value.compare("A") == 0)  ci = std::make_pair(&Controller_1,A);
          else if(value.compare("B") == 0)  ci = std::make_pair(&Controller_1,B);
          else if(value.compare("X") == 0)  ci = std::make_pair(&Controller_1,X);
          else if(value.compare("Y") == 0)  ci = std::make_pair(&Controller_1,Y);
          else if(value.compare("U") == 0)  ci = std::make_pair(&Controller_1,U);
          else if(value.compare("D") == 0)  ci = std::make_pair(&Controller_1,D);
          else if(value.compare("L") == 0)  ci = std::make_pair(&Controller_1,L);
          else if(value.compare("R") == 0)  ci = std::make_pair(&Controller_1,R);
          else if(value.compare("L1") == 0) ci = std::make_pair(&Controller_1,L1);
          else if(value.compare("L2") == 0) ci = std::make_pair(&Controller_1,L2);
          else if(value.compare("R1") == 0) ci = std::make_pair(&Controller_1,R1);
          else if(value.compare("R2") == 0) ci = std::make_pair(&Controller_1,R2);

          action = action.substr(0, action.length()-1);

          for(int i = 0; i < sizeof(action_list)/sizeof(*action_list); i++)
          {
            //std::cout << "Controller_num: " << controller_num << "\n";
            //std::cout << "value: " << value << "\n";
            //std::cout << "action: " << action << "\n";

            //std::cout << "Action: " << action << "; Action List: " << action_list[i] << "\n";

            //std::cout << action_list[i] << " vs " << action << ": " <<action.compare(action_list[i]) << "\n";

            if(action.compare(action_list[i]) == 0)
            {
              //std::cout << action_list[i] << " mapped!\n";
              button_map[action_list[i]] = ci;
            }
          }
        }
        else if(controller_num.compare("Controller 2") == 0)
        {
          if(value.compare("LX") == 0)      ci = std::make_pair(&Controller_2,LX);
          else if(value.compare("LY") == 0) ci = std::make_pair(&Controller_2,LY);
          else if(value.compare("RX") == 0) ci = std::make_pair(&Controller_2,RX);
          else if(value.compare("RY") == 0) ci = std::make_pair(&Controller_2,RY);
          else if(value.compare("A") == 0)  ci = std::make_pair(&Controller_2,A);
          else if(value.compare("B") == 0)  ci = std::make_pair(&Controller_2,B);
          else if(value.compare("X") == 0)  ci = std::make_pair(&Controller_2,X);
          else if(value.compare("Y") == 0)  ci = std::make_pair(&Controller_2,Y);
          else if(value.compare("U") == 0)  ci = std::make_pair(&Controller_2,U);
          else if(value.compare("D") == 0)  ci = std::make_pair(&Controller_2,D);
          else if(value.compare("L") == 0)  ci = std::make_pair(&Controller_2,L);
          else if(value.compare("R") == 0)  ci = std::make_pair(&Controller_2,R);
          else if(value.compare("L1") == 0) ci = std::make_pair(&Controller_2,L1);
          else if(value.compare("L2") == 0) ci = std::make_pair(&Controller_2,L2);
          else if(value.compare("R1") == 0) ci = std::make_pair(&Controller_2,R1);
          else if(value.compare("R2") == 0) ci = std::make_pair(&Controller_2,R2);

          for(int i = 0; i < sizeof(action_list)/sizeof(*action_list); i++)
          {
            if(action.compare(action_list[i]) == 0)
            {
              //std::cout << action_list[i] << " mapped!\n";
              button_map[action_list[i]] = ci;
            }
          }
        }
/*
        for(int i = 0; i < sizeof(action_list)/sizeof(*action_list); i++)
        {
          if(!button_map.count(action_list[i])) // Action not assigned to btn map
          {
            button_map[action_list[i]] = std::make_pair(&Controller_1,Not_Assigned);
          }
        }*/

      }
      itt++;

      //memset(controller_numc, 0, );
      //memset(actionc, 0, 13);
      //memset(valuec, 0, 13);



    }
    free(controller_numc);
    free(actionc);
    free(valuec);
    fclose(profile_file);
  }
  else {std::cout << "File not found\n";}
}

Profile::Profile(std::string profile_file_name)
{
  this->profile_file_name = profile_file_name;
  set_layout(this->profile_file_name);
}



bool isSaving = false;
FILE* save_file;

void save_run(void*)
{
  while(1){
	if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
	{
		isSaving = !isSaving;
    pros::delay(500);
	}
  if(isSaving == true)
  {
    //std::cout << "Start saving!!!\n";
    save_file = fopen("/usd/last_saved_run.csv", "a");

    for(int i = LX; i <= R2; i++)
    {
      controller_input foo = static_cast<controller_input>(i);
      char value[4];
      itoa(controller_1_values[foo], value, 10);
      fputs(value, save_file);
      fputs(",", save_file);
    }
    fputs("\n", save_file);


    fclose(save_file);
  }

	pros::delay(20);
}
}
