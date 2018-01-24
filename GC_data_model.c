// GC-C-IRMS Data Model

// Models GC-C-IRMS process and outputs set of artificial PeakSimple .asc files for data processing.


// Blake Leonard	2014

// Monitor Instruments


#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <linear.h>

#include <math.h>


void main()
{

	int total_runs = 30;
	
	double run_time = 11;                                         			// minutes

	double physical_time_resolution = 0.0001;               			// seconds ( needs to be a factor of 1 )

	double hardware_sampling_time = 0.1;                    			// seconds

	double displacement_time_44_45 = 0.01;                  			// seconds

	
	double pulse_std_44[3];
	
	double pulse_height_44[4];
	
	double pulse_center_44[4];
	
	double ref_pulse_width_44, ref_top_slope_44, ref_side_slope_44;
	
	double ref_pulse_start;
	
	double physical_pdb[4];
	
	double physical_ratio[4];
	
	
	pulse_center_44[0] = 1;								// C1, min
	
	pulse_std_44[0] = 2.5;                              				// seconds

	pulse_height_44[0] = 1000;                          				// mV
	
	physical_pdb[0] = 0;
	
	
	pulse_center_44[1] = 2;								// C2
	
	pulse_std_44[1] = 2.5;                              

	pulse_height_44[1] = 1000;      

	physical_pdb[1] = 0;
	
	
	pulse_center_44[2] = 3;								 // C3
	
	pulse_std_44[2] = 2.5;                             

	pulse_height_44[2] = 1000;    

	physical_pdb[2] = 0;
	
	
	ref_pulse_start = 5;								// Ref

	ref_pulse_width_44 = 36;								
	
	pulse_height_44[3] = 1000;	

	ref_side_slope_44 = 1000;							// mV per sec	
	
	ref_top_slope_44 = 0;
	
	physical_pdb[3] = -39.88;
	

	double peak_exp_decay = 0.99995;

	int sample_noise_flag = 1;

	int johnson_noise_flag = 1;

	int shot_noise_flag = 1; 

	int spillover_noise_flag = 1;

	int collision_noise_flag = 1;

	int misc_noise_flag = 1;

	int osc_flag_44 = 1;
	
	int osc_flag_45 = 1;

	double spillover_percent_44 = 0.0007;                				// Proportion of 44 signal which spills over into 45

	double misc_noise_44_current_std = 0;                    			// mV

	double misc_noise_45_current_std = 0;                    			// mV

	int temp = 300;                                      				// Kelvin

	double pressure = 5E-6;                              				// Torr

	const double co2_diameter = 3.6E-10;                       			// Meters

	const double ion_path_length = 0.1;                        			// Meters

	const double bandwidth = 50;                               			// Hertz

	const double resistance_44 = 1E8;                          			// Ohms

	const double resistance_45 = 1E10;                         			// Ohms
	
	double osc_amplitude_44 = 0.025;					       	// mV	
	
	double osc_amplitude_45 = 0.125;                           			// mV
	
	double osc_freq_44 = 0.025;                          				// Hertz
	
	double osc_freq_45 = 0.025;                           				// Hertz
	
	double max_inter_run_time = 20;                      				// seconds
	
	double gc_pdb_drift = 1;							// pdb per hour
	
	double ref_pdb_drift = 1;							// pdb per hour
	


	const double q = 1.602E-19;                                			// Coulombs per ion

	const double k = 1.38E-23;                                 			// Boltzmann's Constant
	
	
	FILE *ifp, *ofp1, *ofp2;
	
	char *mode = "r";
	
	char line[256];
	
	int word_count, i, j;
	
	double d;
	
	char * next_word_ptr;
	
	
	// Open and Read Settings File
	
	char settings_file[] = "data_model_settings.txt";
	
	ifp = fopen(settings_file, mode);
	
	if (ifp == NULL) 
	{
		fprintf(stderr, "Can't open settings file.  Using internal settings.\n\n");
	}
	else
	{
			
		// Read in Total Runs
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				total_runs = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Run Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				run_time = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Physical Time Resolution
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				physical_time_resolution = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Hardware Sampling Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				hardware_sampling_time = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in 44/45 Displacement Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				displacement_time_44_45 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in C1 Settings
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				pulse_center_44[0] = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				pulse_std_44[0] = d;                        
			
			}
			else if ( word_count == 3 )
			{
				d = atof(next_word_ptr);
					
				pulse_height_44[0] = d;                        
			
			}
			else if ( word_count == 4 )
			{
				d = atof(next_word_ptr);
					
				physical_pdb[0] = d;                        
			
			}	

			word_count++;

			next_word_ptr = strtok(NULL,",");

		}
		
		
		// Read in C2 Settings
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				pulse_center_44[1] = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				pulse_std_44[1] = d;                        
			
			}
			else if ( word_count == 3 )
			{
				d = atof(next_word_ptr);
					
				pulse_height_44[1] = d;                        
			
			}
			else if ( word_count == 4 )
			{
				d = atof(next_word_ptr);
					
				physical_pdb[1] = d;                        
			
			}	

			word_count++;

			next_word_ptr = strtok(NULL,",");

		}
		
		
		// Read in C3 Settings
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				pulse_center_44[2] = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				pulse_std_44[2] = d;                        
			
			}
			else if ( word_count == 3 )
			{
				d = atof(next_word_ptr);
					
				pulse_height_44[2] = d;                        
			
			}
			else if ( word_count == 4 )
			{
				d = atof(next_word_ptr);
					
				physical_pdb[2] = d;                        
			
			}	

			word_count++;

			next_word_ptr = strtok(NULL,",");

		}
		
		
		// Read in Ref Settings
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				ref_pulse_start = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				ref_pulse_width_44 = d;                        
			
			}
			else if ( word_count == 3 )
			{
				d = atof(next_word_ptr);
					
				pulse_height_44[3] = d;                        
			
			}
			else if ( word_count == 4 )
			{
				d = atof(next_word_ptr);
					
				physical_pdb[3] = d;                        
			
			}	
			else if ( word_count == 5 )
			{
				d = atof(next_word_ptr);
					
				ref_side_slope_44 = d;                        
			
			}
			else if ( word_count == 6 )
			{
				d = atof(next_word_ptr);
					
				ref_top_slope_44 = d;                        
			
			}
			
			word_count++;

			next_word_ptr = strtok(NULL,",");

		}
		
		
		// Read Exponential Decay Factor
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				peak_exp_decay = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Spillover Pct
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				spillover_percent_44 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Misc Noise 44 Std
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				misc_noise_44_current_std = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Misc Noise 45 Std
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				misc_noise_45_current_std = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Electrometer Temp
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				temp = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Pressure
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				pressure = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in 44 Oscillation Amplitude
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				osc_amplitude_44 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in 45 Oscillation Amplitude
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				osc_amplitude_45 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in 44 Oscillation Freq
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				osc_freq_44 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in 45 Oscillation Freq
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				osc_freq_45 = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Max Inter Run Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				max_inter_run_time = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in GC PDB Drift
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				gc_pdb_drift = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Ref PDB Drift
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				ref_pdb_drift = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Sampling Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				sample_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Johnson Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				johnson_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Shot Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				shot_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Spillover Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				spillover_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Collision Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				collision_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Misc Noise Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				misc_noise_flag = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Oscillation 44 Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				osc_flag_44 = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
		
		// Read in Oscillation 45 Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				osc_flag_45 = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
	}
			
	
	int istep, jstep, kstep, lstep, pstep, rstep;
	
	
	// convert drift from pdb per hour to pdb per run
	
	gc_pdb_drift = gc_pdb_drift * ( run_time / 60 );
	
	ref_pdb_drift = ref_pdb_drift * ( run_time / 60 );
	
	
	// convert from mV to amps & min to sec
	
	for ( istep = 0; istep < 4; istep ++ )
	{
	
		pulse_height_44[istep] = ( pulse_height_44[istep] / 1000 ) / resistance_44;
		
		pulse_center_44[istep] = pulse_center_44[istep] * 60;
	
	}
	
	misc_noise_44_current_std = ( misc_noise_44_current_std / 1000 ) / resistance_44;
	
	misc_noise_45_current_std = ( misc_noise_45_current_std / 1000 ) / resistance_45;
	
	osc_amplitude_44 = ( osc_amplitude_44 / 1000 ) / resistance_44;
	
	osc_amplitude_45 = ( osc_amplitude_45 / 1000 ) / resistance_45;
	
	ref_side_slope_44 = ( ref_side_slope_44 / 1000 ) / resistance_44;
	
	ref_top_slope_44 = ( ref_top_slope_44 / 1000 ) / resistance_44;
	
	run_time = run_time * 60; 
	
	ref_pulse_start = ref_pulse_start * 60;
	

	const double pressure_pas = pressure * 133.322;            // Convert to Pascals

	const double mean_free_path = ( k * temp ) / ( sqrt(2) * 3.141592 * co2_diameter * co2_diameter * pressure_pas );

	const double collision_prob = ion_path_length / mean_free_path;

	const double collision_prob_44_corr = collision_prob - spillover_percent_44;


	double temp_displacement_step_44_45;

	int displacement_step_44_45;

	double offset_time;

	double temp_offset_step;

	int offset_step;


	const double temp_hardware_sampling_time_ratio = hardware_sampling_time / physical_time_resolution;        	// needs to be an integer

	const int hardware_sampling_time_ratio = floor(temp_hardware_sampling_time_ratio + 0.5 );


	char a;


	const double physical_sampling_points_temp = run_time / physical_time_resolution;                       	// needs to be an integer

	const int physical_sampling_points = floor(physical_sampling_points_temp + 0.5);                 

	const double hardware_sampling_points_temp = run_time / hardware_sampling_time;                         	// needs to be an integer

	const int hardware_sampling_points = floor(hardware_sampling_points_temp + 0.5);   
	
	
	ref_pulse_start = ref_pulse_start / physical_time_resolution;

	const int ref_pulse_start_point = floor (ref_pulse_start + 0.5);
	
	
	const double ref_side_length_44 = pulse_height_44[3] / ref_side_slope_44;                              

	const double temp_ref_side_steps_44 = ref_side_length_44 / physical_time_resolution;                      	// needs to be an integer

	const double ref_side_steps_44 = floor(temp_ref_side_steps_44 + 0.5);

	const double ref_top_length_44 = ref_pulse_width_44 - (2 * ref_side_length_44 );                        	// needs to be positive

	const double temp_ref_top_steps_44 = ref_top_length_44 / physical_time_resolution;                    		// needs to be an integer

	const double ref_top_steps_44 = floor(temp_ref_top_steps_44 + 0.5); 
	

	double u, v, r;

	double random_normal;

	double total_charge;

	double total_ions;

	double sampling_noise_percent_std;
	
	double sampling_noise_ion_std;
	
	double sampling_noise_current_std;

	double sampling_noise_current; 
	

	const double johnson_noise_current_44_std = sqrt ( ( 4 * k * temp * bandwidth ) / resistance_44 );

	const double johnson_noise_current_45_std = sqrt ( ( 4 * k * temp * bandwidth ) / resistance_45 );

	double johnson_noise_current_44;

	double johnson_noise_current_45;


	const double shot_noise_current_std_coeff = sqrt (2 * q * bandwidth );

	double shot_noise_current_44_std;

	double shot_noise_current_45_std;

	double shot_noise_current_44;

	double shot_noise_current_45;


	double charge_44; 

	double ions_44;

	double spillover_noise_percent_std;
	
	double spillover_noise_ion_std;
	
	double spillover_noise_current_std;
	
	double spillover_noise_current;


	double charge_45;

	double ions_45;

	double collision_noise_44_percent_std;
	
	double collision_noise_44_ion_std;
	
	double collision_noise_44_current_std;
	
	double collision_noise_44_current;

	double collision_noise_45_percent_std;
	
	double collision_noise_45_ion_std;
	
	double collision_noise_45_current_std;
	
	double collision_noise_45_current;

	double misc_noise_44_current;

	double misc_noise_45_current;
	

	static double physical_pulse_function_44[10000000];

	static double physical_pulse_function_45[10000000];

	static double original_physical_pulse_function_45[10000000];

	static double original_hardware_pulse_function_44[1000000];

	static double original_hardware_pulse_function_45[1000000];

	static double hardware_pulse_function_44[1000000];

	static double hardware_pulse_function_45[1000000];
	
	static double temp_physical_pulse_function_44[100000000];
	
	static double temp_original_physical_pulse_function_45[100000000];
	
	
	double osc_phase_44 = 0, osc_phase_45 = 0;
	
	double rand_inter_run_time;

	srand(time(0));

	int f = 100;
	
	char outputFilename1[32], outputFilename2[32];
	
	printf("\n");
	
	for ( rstep = 0; rstep < total_runs; rstep ++ )
	{
	
		// Open Output files
	
		sprintf(outputFilename1, "CH1 %i.asc", f ); 

		ofp1 = fopen(outputFilename1, "w");

		if (ofp1 == NULL) {

		  fprintf(stderr, "Can't open output file %s!\n", outputFilename1);

		  return;
		}
		
		sprintf(outputFilename2, "CH2 %i.asc", f ); 

		ofp2 = fopen(outputFilename2, "w");

		if (ofp2 == NULL) {

		  fprintf(stderr, "Can't open output file %s!\n", outputFilename2);

		  return;
		}
	
		
		// Insert Peak Simple File Headers
		
		fprintf(ofp1,"<TYPE>=CHROM\n");
			
		fprintf(ofp1,"<LAB NAME>=SRI Instruments\n");
		
		fprintf(ofp1,"<CLIENT>=Valued Customer\n");
		
		fprintf(ofp1,"<CLIENT ID>=N2024\n");
		
		fprintf(ofp1,"<COLLECTION DATE>=\n");
		
		fprintf(ofp1,"<HOLDING TIME>=\n");
		
		fprintf(ofp1,"<METHOD>=Syringe Injection\n");
		
		fprintf(ofp1,"<LAB ID>=\n");
		
		fprintf(ofp1,"<DESCRIPTION>=44\n");
		
		fprintf(ofp1,"<COLUMN>=RESTEK 15METER MXT-1\n");
		
		fprintf(ofp1,"<CARRIER>=HELIUM AT 5 PSI\n");
		
		fprintf(ofp1,"<TEMPERATURE>=\n");
		
		fprintf(ofp1,"<EVENTS>=\n");
		
		fprintf(ofp1,"<COMPONENTS>=DataSys44.cpt\n");
		
		fprintf(ofp1,"<SAMPLE>=RUN1\n");
		
		fprintf(ofp1,"<OPERATOR>=\n");
		
		fprintf(ofp1,"<QC BATCH>=\n");
		
		fprintf(ofp1,"<CONDITIONS>=Data Model Generated\n");
		
		fprintf(ofp1,"<DATE>= 1- 1-2020\n");
		
		fprintf(ofp1,"<TIME>=00:00:00\n");
		
		if ( hardware_sampling_time == 0.5 )
		{
		
			fprintf(ofp1,"<RATE>=2Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.2 )
		{
		
			fprintf(ofp1,"<RATE>=5Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.1 )
		{
		
			fprintf(ofp1,"<RATE>=10Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.05 )
		{
		
			fprintf(ofp1,"<RATE>=20Hz\n");
			
		}
		
		fprintf(ofp1,"<SIZE>=%d\n", hardware_sampling_points);
		
		fprintf(ofp1,"<SAMP WEIGHT>=1.000000\n");
		
		fprintf(ofp1,"<STD WEIGHT>=1.000000\n");
		
		fprintf(ofp1,"<CONTROL FILENAME>=DEFAULT.CON\n");
		
		
		fprintf(ofp2,"<TYPE>=CHROM\n");
			
		fprintf(ofp2,"<LAB NAME>=SRI Instruments\n");
		
		fprintf(ofp2,"<CLIENT>=Valued Customer\n");
		
		fprintf(ofp2,"<CLIENT ID>=N2024\n");
		
		fprintf(ofp2,"<COLLECTION DATE>=\n");
		
		fprintf(ofp2,"<HOLDING TIME>=\n");
		
		fprintf(ofp2,"<METHOD>=Syringe Injection\n");
		
		fprintf(ofp2,"<LAB ID>=\n");
		
		fprintf(ofp2,"<DESCRIPTION>=45\n");
		
		fprintf(ofp2,"<COLUMN>=RESTEK 15METER MXT-1\n");
		
		fprintf(ofp2,"<CARRIER>=HELIUM AT 5 PSI\n");
		
		fprintf(ofp2,"<TEMPERATURE>=\n");
		
		fprintf(ofp2,"<EVENTS>=\n");
		
		fprintf(ofp2,"<COMPONENTS>=DataSys44.cpt\n");
		
		fprintf(ofp2,"<SAMPLE>=RUN1\n");
		
		fprintf(ofp2,"<OPERATOR>=\n");
		
		fprintf(ofp2,"<QC BATCH>=\n");
		
		fprintf(ofp2,"<CONDITIONS>=Data Model Generated\n");
		
		fprintf(ofp2,"<DATE>= 1- 1-2020\n");
		
		fprintf(ofp2,"<TIME>=00:00:00\n");
		
		if ( hardware_sampling_time == 0.5 )
		{
		
			fprintf(ofp2,"<RATE>=2Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.2 )
		{
		
			fprintf(ofp2,"<RATE>=5Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.1 )
		{
		
			fprintf(ofp2,"<RATE>=10Hz\n");
			
		}
		else if ( hardware_sampling_time == 0.05 )
		{
		
			fprintf(ofp2,"<RATE>=20Hz\n");
			
		}
		
		fprintf(ofp2,"<SIZE>=%d\n", hardware_sampling_points);
		
		fprintf(ofp2,"<SAMP WEIGHT>=1.000000\n");
		
		fprintf(ofp2,"<STD WEIGHT>=1.000000\n");
		
		fprintf(ofp2,"<CONTROL FILENAME>=DEFAULT.CON\n");
		
		
		f++;
	
	
		for ( istep = 0; istep < physical_sampling_points; istep ++ )
		{
		
			physical_pulse_function_44[istep] = 0;
			
			original_physical_pulse_function_45[istep] = 0;
			
		}
	
		// compose physical GC pulse functions
		
		for ( pstep = 0; pstep < 3; pstep ++ )
		{
		
			physical_ratio[pstep] = 0.0112372 * ( 1 + ( ( physical_pdb[pstep] + ( rstep * gc_pdb_drift ) ) / 1000 ) );
		
			for ( istep = 0; istep < physical_sampling_points; istep ++ )
			{

				temp_physical_pulse_function_44[istep] = pulse_height_44[pstep] * exp ( ( - ( istep * physical_time_resolution - pulse_center_44[pstep] ) * ( istep * physical_time_resolution - pulse_center_44[pstep] )   ) / ( 2 * pulse_std_44[pstep] * pulse_std_44[pstep] ) );

				if ( istep != 0 )
				{

					temp_physical_pulse_function_44[istep] = ( ( 1 - peak_exp_decay ) * temp_physical_pulse_function_44[istep] ) + ( peak_exp_decay * temp_physical_pulse_function_44[istep - 1] );

				}

				temp_original_physical_pulse_function_45[istep] = physical_ratio[pstep] * temp_physical_pulse_function_44[istep];

				physical_pulse_function_44[istep] += temp_physical_pulse_function_44[istep];
			
				original_physical_pulse_function_45[istep] += temp_original_physical_pulse_function_45[istep];
			
			}
			
		}
		
		
		// Compose REF physical pulse function		
		
		physical_ratio[3] = 0.0112372 * ( 1 + ( ( physical_pdb[3] + ( rstep * ref_pdb_drift ) ) / 1000 ) );
		
		for ( istep = 0; istep < physical_sampling_points; istep ++ )
		{

			if ( istep < ref_pulse_start_point )
			{
			
				temp_physical_pulse_function_44[istep] = 0;

			}
			else if ( ( istep >= ref_pulse_start_point ) & ( istep < ( ref_side_steps_44 + ref_pulse_start_point ) ) )
			{

				temp_physical_pulse_function_44[istep] = ref_side_slope_44 * ( ( istep - ref_pulse_start_point + 1 ) * physical_time_resolution );

			}
			else if ( ( istep >= ( ref_side_steps_44 + ref_pulse_start_point ) ) & ( istep < ( ref_side_steps_44 + ref_top_steps_44 + ref_pulse_start_point ) ) )
			{

				temp_physical_pulse_function_44[istep] = pulse_height_44[3] + ref_top_slope_44 * ( ( istep - ( ref_side_steps_44 + ref_pulse_start_point + 1 )) * physical_time_resolution );

			}
			else if ( ( istep >= ( ref_side_steps_44 + ref_top_steps_44 + ref_pulse_start_point )) & ( istep < (ref_side_steps_44 + ref_side_steps_44 + ref_top_steps_44 + ref_pulse_start_point ) ))
			{

				temp_physical_pulse_function_44[istep] = (pulse_height_44[3] + ( ref_top_slope_44 * ref_top_length_44 ) ) - ( ref_side_slope_44 * ( istep - ( ref_side_steps_44 + ref_top_steps_44 + ref_pulse_start_point ) ) * physical_time_resolution );

			}
			else if ( istep >= ( ref_side_steps_44 + ref_side_steps_44 + ref_top_steps_44 + ref_pulse_start_point ))
			{

				temp_physical_pulse_function_44[istep] = 0;

			}


			// exponential decay tailing for ref

			if ( istep != 0 )
			{

				temp_physical_pulse_function_44[istep] = ( ( 1 - peak_exp_decay ) * temp_physical_pulse_function_44[istep] ) + ( peak_exp_decay * temp_physical_pulse_function_44[istep - 1] );

			}
			
			
			temp_original_physical_pulse_function_45[istep] = physical_ratio[3] * temp_physical_pulse_function_44[istep];

			physical_pulse_function_44[istep] += temp_physical_pulse_function_44[istep];
			
			original_physical_pulse_function_45[istep] += temp_original_physical_pulse_function_45[istep];			
			
		}
						

		// Physically Offset 45 Pulse Function

		temp_displacement_step_44_45 = displacement_time_44_45 / physical_time_resolution;

		displacement_step_44_45 = floor(temp_displacement_step_44_45 + 0.5);


		for ( istep = physical_sampling_points; istep < (physical_sampling_points + displacement_step_44_45 ); istep ++ )
		{

			original_physical_pulse_function_45[istep] = 0;

		}
		

		for ( istep = 0; istep < physical_sampling_points; istep ++ )
		{

			physical_pulse_function_45[istep] = original_physical_pulse_function_45[istep + displacement_step_44_45];

		}
		

		offset_time = ( 0.89 * (float)rand()/RAND_MAX ) * hardware_sampling_time;

		if ( offset_time < physical_time_resolution )
		{

			offset_time = offset_time + physical_time_resolution;

		}

		temp_offset_step = offset_time / physical_time_resolution;

		offset_step = floor(temp_offset_step + 0.5);

		
		// Sample Pulses in Hardware

		for ( istep = 0; istep < hardware_sampling_points; istep ++ )
		{	

			hardware_pulse_function_44[istep] = 0;

			hardware_pulse_function_45[istep] = 0;


			// Average over sampling interval

			for ( kstep = 0; kstep < hardware_sampling_time_ratio; kstep ++ )
			{

				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] + physical_pulse_function_44[( istep * hardware_sampling_time_ratio ) + kstep + offset_step];    
		
				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + physical_pulse_function_45[( istep * hardware_sampling_time_ratio ) + kstep + offset_step];    

			}


			hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] / hardware_sampling_time_ratio;

			hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] / hardware_sampling_time_ratio;


			original_hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep];

			original_hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep];

 
			// Add Sampling Noise

			if ( ( sample_noise_flag == 1 ) & ( ( original_hardware_pulse_function_45[istep] + original_hardware_pulse_function_44[istep] ) > 0  ) )
			{

				total_charge = ( original_hardware_pulse_function_44[istep] + original_hardware_pulse_function_45[istep] ) * hardware_sampling_time;

				total_ions = total_charge / q;

				sampling_noise_percent_std = ( ( 0.0111123 * .9888877 ) / ( sqrt ( total_ions ) ) ) ;

				sampling_noise_ion_std = sampling_noise_percent_std * total_ions;

				sampling_noise_current_std = ( sampling_noise_ion_std * q ) / hardware_sampling_time;


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);

				sampling_noise_current = random_normal * sampling_noise_current_std;


				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + sampling_noise_current;

				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] - sampling_noise_current;

			}


			// Add Johnson Noise
			
			if ( johnson_noise_flag == 1 )
			{

				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);

				johnson_noise_current_44 = random_normal * johnson_noise_current_44_std; 


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				johnson_noise_current_45 =  random_normal * johnson_noise_current_45_std;

				
				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] + johnson_noise_current_44;

				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + johnson_noise_current_45;

			}


			// Add Shot Noise

			if (shot_noise_flag == 1 )
			{

				shot_noise_current_44_std = shot_noise_current_std_coeff * sqrt ( original_hardware_pulse_function_44[istep] );

				shot_noise_current_45_std = shot_noise_current_std_coeff * sqrt ( original_hardware_pulse_function_45[istep] );


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);

				shot_noise_current_44 = random_normal * shot_noise_current_44_std; 


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				shot_noise_current_45 = random_normal * shot_noise_current_45_std;

				
				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] + shot_noise_current_44;

				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + shot_noise_current_45;

			}


			// Add Spillover & Spillover Noise

			if( ( spillover_noise_flag == 1 ) & ( original_hardware_pulse_function_44[istep] > 0 )  )
			{

				charge_44 = original_hardware_pulse_function_44[istep] * hardware_sampling_time;

				ions_44 = charge_44 / q;

				spillover_noise_percent_std = ( ( spillover_percent_44  * ( 1 - spillover_percent_44 ) ) / ( sqrt ( ions_44 ) ) ) ;

				spillover_noise_ion_std = spillover_noise_percent_std * ions_44;

				spillover_noise_current_std = ( spillover_noise_ion_std * q ) / hardware_sampling_time;


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				spillover_noise_current = random_normal * spillover_noise_current_std;


				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + ( spillover_percent_44 * original_hardware_pulse_function_44[istep] ) + spillover_noise_current;

				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] - ( spillover_percent_44 * original_hardware_pulse_function_44[istep] ) - spillover_noise_current;

			}


			// Add Collision Noise

			if ( ( collision_noise_flag == 1 ) & ( original_hardware_pulse_function_44[istep] > 0  ) & ( original_hardware_pulse_function_45[istep] > 0  ) )
			{

				// 44 Collision Noise

				if ( collision_prob_44_corr > 0 )
				{

					charge_44 = original_hardware_pulse_function_44[istep] * hardware_sampling_time;

					ions_44 = charge_44 / q;

					collision_noise_44_percent_std = ( ( collision_prob_44_corr  * ( 1 - collision_prob_44_corr ) ) / ( sqrt ( ions_44 ) ) ) ;

					collision_noise_44_ion_std = collision_noise_44_percent_std * ions_44;

					collision_noise_44_current_std = ( collision_noise_44_ion_std * q ) / hardware_sampling_time;


					u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

					while ( u == 0 )
					{

						u = (float)rand()/RAND_MAX;

					}

					v = (float)rand()/RAND_MAX;

					r = sqrt( (-2) * log(u) );

					random_normal = r * sin(2 * 3.141592 * v);
					
					collision_noise_44_current = random_normal * collision_noise_44_current_std;

					hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] - ( collision_prob_44_corr * original_hardware_pulse_function_44[istep] ) + collision_noise_44_current;

				}


				// 45 Collision Noise

				charge_45 = original_hardware_pulse_function_45[istep] * hardware_sampling_time;

				ions_45 = charge_45 / q;

				collision_noise_45_percent_std = ( ( collision_prob  * ( 1 - collision_prob ) ) / ( sqrt ( ions_45 ) ) ) ;

				collision_noise_45_ion_std = collision_noise_45_percent_std * ions_45;

				collision_noise_45_current_std = ( collision_noise_45_ion_std * q ) / hardware_sampling_time;


				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				collision_noise_45_current = random_normal * collision_noise_45_current_std;

				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] - ( collision_prob * original_hardware_pulse_function_45[istep] ) + collision_noise_45_current;

			}


			// Add Misc Noise

			if ( misc_noise_flag == 1 )
			{

				// 44 Misc Noise
				
				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				misc_noise_44_current = random_normal * misc_noise_44_current_std;

				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] + misc_noise_44_current;


				// 45 Misc Noise

				u = (float)rand()/RAND_MAX;      // Generate random number from  normal dist

				while ( u == 0 )
				{

					u = (float)rand()/RAND_MAX;

				}

				v = (float)rand()/RAND_MAX;

				r = sqrt( (-2) * log(u) );

				random_normal = r * sin(2 * 3.141592 * v);
				
				misc_noise_45_current = random_normal * misc_noise_45_current_std;

				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + misc_noise_45_current;

			}
			
			
			// Add 44 Electronic Oscillation 
			
			if ( osc_flag_44 == 1 )
			{
			
				hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] + osc_amplitude_44 * sin ( 2 * 3.141592 * osc_freq_44 * istep * hardware_sampling_time + osc_phase_44 );
			
			}
			
			
			// Add 45 Electronic Oscillation 
			
			if ( osc_flag_45 == 1 )
			{
			
				hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] + osc_amplitude_45 * sin ( 2 * 3.141592 * osc_freq_45 * istep * hardware_sampling_time + osc_phase_45 );
			
			}
			
			
			// Convert from Amps to uV and round
			
			hardware_pulse_function_44[istep] = hardware_pulse_function_44[istep] * resistance_44 * 1E6;
			
			hardware_pulse_function_44[istep] = floor( hardware_pulse_function_44[istep] + 0.5 );
			
			hardware_pulse_function_45[istep] = hardware_pulse_function_45[istep] * resistance_45 * 1E6;
			
			hardware_pulse_function_45[istep] = floor( hardware_pulse_function_45[istep] + 0.5 );
			
			fprintf(ofp1, "%.0f, 0\n", hardware_pulse_function_44[istep] );
			
			fprintf(ofp2, "%.0f, 0\n", hardware_pulse_function_45[istep] );			
			
		}
		
		rand_inter_run_time = max_inter_run_time * (float)rand()/RAND_MAX;
		
		osc_phase_44 += 2 * 3.141592 * osc_freq_44 * ( ( hardware_sampling_points * hardware_sampling_time ) + rand_inter_run_time );
		
		osc_phase_45 += 2 * 3.141592 * osc_freq_45 * ( ( hardware_sampling_points * hardware_sampling_time ) + rand_inter_run_time );
		
		
		fclose(ofp1);
		
		fclose(ofp2);
		
		printf("Run %d Complete\n", rstep + 1 );
	
	}
	
	return;

}