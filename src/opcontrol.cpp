#include "main.h"

pros::Task update_controller_values_task(update_controller_values, NULL);

void playback(void*)
{
	while(1)
	{
		if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
		{
			update_controller_values_task.suspend();
			playback_run("last_saved_run");
		}
		if(!isInPlayback)
		{
			update_controller_values_task.resume();
		}
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Task playback_task(playback, NULL);
	pros::Task save_run_task(save_run, NULL);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);
	Profile DefaultProf;
	Profile BrandonProf("profile-Brandon");

	Active_Profile = DefaultProf;

	while (true) {
		if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
		{
			Active_Profile = DefaultProf;
			pros::lcd::print(3, "Default Profile Loaded");
		}
		else if(Controller_1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
		{
			Active_Profile = BrandonProf;
			pros::lcd::print(3, "Brandon Profile Loaded");
		}
		pros::lcd::print(0, "%d %d %d", (Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) >> 2,
		                 (Active_Profile.button_map["Drive 2"].second) >> 1,
		                 (controller_1_values[Active_Profile.button_map["Drive 2"].second]) >> 0);


		left_mtr = 100;//Controller_1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		//std::cout << "Speed: " << "\n";
		//std::cout << Active_Profile.button_map["Drive 2"].second << "\n";

		// driveLift(controller_2_values[LY]); //-127->127
		if(Active_Profile.button_map["Drive 2"].second != Not_Assigned)
		{

			int speed = (Active_Profile.button_map["Drive 2"].first == &Controller_1)?
			 						controller_1_values[Active_Profile.button_map["Drive 2"].second]:
									controller_2_values[Active_Profile.button_map["Drive 2"].second];

									//std::cout << speed << "\n";


			right_mtr = speed;
		}
		else
		{
			std::cout << "NOT FOUND" << "\n";
		}



		pros::delay(20);
	}
}
