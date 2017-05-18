#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
#include <dynamixel_workbench_msgs/DynamixelCommand.h>

using namespace std;

class Dynamixel{
private:
	ros::NodeHandle n;
	ros::Publisher pub_n;
public:
	Dynamixel();
	int moveMotor(double position);
	void torque_enable(int _enable);

};


Dynamixel::Dynamixel(){
	pub_n = n.advertise<dynamixel_workbench_msgs::DynamixelCommand>("/dynamixel_workbench_single_manager/motor_command", 1000);
	torque_enable(1);


}
void Dynamixel::torque_enable(int _enable)
{
	dynamixel_workbench_msgs::DynamixelCommand aux;
	aux.addr_name = "torque_enable";
	aux.value = _enable;
	pub_n.publish(aux);
	//ROS_INFO("set torque: %d", _enable);
}
int Dynamixel::moveMotor(double position)
{
	dynamixel_workbench_msgs::DynamixelCommand aux;
	aux.addr_name = "goal_position";
	aux.value = position;
	pub_n.publish(aux);
	ROS_INFO("set position: %.0f", position);
	return 1;
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "example4_move_motor");
	usleep(100 * 1000);
	Dynamixel motors;
	motors.torque_enable(1);
	usleep(100 * 1000);

	float counter = 0;
	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		motors.torque_enable(1);
		if (counter < 4096)
		{
			motors.moveMotor(counter);
			counter += 30;
		}
		else{
			counter = 0;
		}
		loop_rate.sleep();
	}
}

