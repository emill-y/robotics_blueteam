#include "devices.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motor_group.hpp"

// Smart Port Devices
pros::MotorGroup left_motors({11, 12}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({10, 18}, pros::MotorGearset::blue);

pros::Imu inertial_sensor(7);
pros::Rotation horizontal_rotation_sensor(-9);
pros::Rotation vertical_rotation_sensor(-11);

pros::MotorGroup intake_belt({12}, pros::MotorGearset::blue);
pros::MotorGroup intake_rollers({13}, pros::MotorGearset::blue);
pros::MotorGroup gear_grabber({20}, pros::MotorGearset::blue);

// 3-Wire Devices
//pros::adi::DigitalOut grabber_piston('A', LOW);

// Wireless Devices
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

// Drivetrain Configuration
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 11.75,
                              lemlib::Omniwheel::NEW_275, 360, 2);

// PID Tuning
lemlib::ControllerSettings lateral_controller(12, 0, 5, 3, 1, 100, 3, 500, 0);
lemlib::ControllerSettings angular_controller(3, 0, 10, 3, 1, 100, 3, 500, 0);

// Odometry Configuration
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rotation_sensor,
                                                lemlib::Omniwheel::NEW_275, 8);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_rotation_sensor,
                                              lemlib::Omniwheel::NEW_275,
                                              -9);

lemlib::OdomSensors odometry_sensors(&vertical_tracking_wheel, nullptr,
                                     &horizontal_tracking_wheel, nullptr,
                                     &inertial_sensor);

// Input Scaling
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steering_curve(3, 10, 1.019);

// LemLib Chassis (Drivetrain + PID + Odometry)
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        odometry_sensors, &throttle_curve, &steering_curve);