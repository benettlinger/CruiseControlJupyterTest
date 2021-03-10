//
// Created by localuser on 3/10/2021.
//
#include "CAN-Functions.h"
#ifndef C_VERSION_VEHICLE_MODEL_FUNCTIONS_H
#define C_VERSION_VEHICLE_MODEL_FUNCTIONS_H

#endif //C_VERSION_VEHICLE_MODEL_FUNCTIONS_H

// User Defined Variables (TO DO: Replace with input prompt)
float initial_speed = 55;  //KPH (Consider user selection)
float dist_prev = 0;
float dist = 0;
float prev_speed = initial_speed;
float current_speed = initial_speed;
float accelerator_pedal_position = 0;
bool checks = True;
float timing_interval = 0.1; // Seconds

// Vehicle parameters
float vehicle_mass = 11793;  // kilograms
float track_inertia = 1.03 * vehicle_mass;  // What is track inertia? Truck inertia?

// Constraints in quadratic function for steady  state road loading
float a = 579;  // Newtons
float b = 0; // N/kph
float c = 0.241512; // N/kph^2
float ratedP = 179; // kW

// Grade schedule
float gradiant = {0, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1}; //Read in from csv?
float distance = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2}; // Might not be needed

int j_max = sizeof(gradiant);
int k_max = sizeof(distance); // Superfluous
float d_max = distance[sizeof(distance)-1]; // Total trip length

float n = [0];
float j = 0;
float k = 0;
float z = [0];

float vehicle_model_speed(accelerator_pedal_position,){
    int app_mult = 1; // Resolution from J1939
    int app_b = -125; //Offset from J1939
    char arb_id[4];
    char data[8];
    bool waiting = True;
    while(waiting){
        can_receive(channel, arb_id, dlc, data);

        }
}


