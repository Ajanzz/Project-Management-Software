#ifndef A1_FUNCTIONS_H
#define A1_FUNCTIONS_H
#include "a1_data_structures.h"
#include <stdbool.h>




unsigned short int get_input_usi(void);


float get_input_f(void);

void init_activity(activity_t * activity_to_int);

void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities);

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities);

void print_main_menu(void);


void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities);


void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities);


void update_activity(activity_t * activity_to_update);

void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);


void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project);


void check_dupes_activity_ids(milestone_t milestone_list[], int num_milestones, int number_activities[]);

void check_dupes_milestone_ids(milestone_t milestone_list[], int num_milestones);







#endif
