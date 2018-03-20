/*
 * tavr_app.h
 *
 *  Created on: Mar 16, 2018
 *      Author: js
 */

#ifndef AVANET_TAVR_APP_H_
#define AVANET_TAVR_APP_H_
#include <app.h>
#include <random.h>
#include "tavr_traffic_pkt.h"
#include <timer-handler.h>

class TAVRApp;
class SendtavrTimer : public TimerHandler{
public:
	SendtavrTimer(TAVRApp* t):TimerHandler(),t_(t){}
	inline void expire(Event*);
protected:
	TAVRApp* t_;
};

class ReplytavrTimer : public TimerHandler{
public:
	ReplytavrTimer(TAVRApp* t):TimerHandler(),t_(t){}
	inline void expire(Event*);
protected:
	TAVRApp* t_;
};



class TAVRApp : public Application{
	friend class  SendtavrTimer;
	friend class  ReplytavrTimer;
public:
	TAVRApp();
	~TAVRApp();
	void stimeout();
	void rtimeout();
	int get_type_node();
	int	get_id();
protected:
	void send_tavr_pkt();
	void recv_msg(int, hdr_wired_infos*);
	void recv_msg(int, hdr_veh_hello*);
	void start();
	void stop();
	inline double next();
	int command(int argc, const char*const* argv);

	inline double* get_laest_update_tstamp_list(){return laest_update_tstamp_list;}
	inline int16_t* get_vehicle_id_list(){return vehicle_id_list;}
	inline int16_t* get_wired_id_list(){return wired_id_list;}
	inline float* get_vehicle_position_x_list(){return vehicle_position_x_list;}
	inline float* get_vehicle_position_y_list(){return vehicle_position_y_list;}
	inline float* get_vehicle_speed_list(){return vehicle_speed_list;}

	inline u_int8_t* get_vehicle_direction_list(){return vehicle_direction_list;}
	inline int16_t* get_bs_id_list(){return bs_id_list;}
	inline u_int8_t* get_junc_row_prev_list(){return junc_row_prev_list;}
	inline u_int8_t* get_junc_col_prev_list(){return junc_col_prev_list;}
	inline u_int8_t* get_junc_row_next_list(){return junc_row_next_list;}
	inline u_int8_t* get_junc_col_next_list(){return junc_col_next_list;}
	inline double& get_send_interval() {return send_interval_;}

	void prepare_data_for_Agent();
	//timer oriented
	SendtavrTimer	tsend_timer;
	ReplytavrTimer	treply_timer;
private:

	double send_interval_;
	double reply_interval_;
	int running_;
//installation type index
	int		type_of_node;
//vehicle oriented
	int		node_id;
	int		seqno_;
	int 	pktsize_;          // Application data packet size
	int		comm_id;


	//wired oriented


	//to sink
	double		laest_update_tstamp_list[VEHICULAR_AMOUNT];	//msg Sent timestamp
	int16_t 	vehicle_id_list[VEHICULAR_AMOUNT]; //device ID----vehicle----save storage
	int16_t 	wired_id_list[VEHICULAR_AMOUNT]; //device ID----vehicle----save storage
	float 		vehicle_position_x_list[VEHICULAR_AMOUNT]; //
	float	 	vehicle_position_y_list[VEHICULAR_AMOUNT]; //
	float		vehicle_speed_list[VEHICULAR_AMOUNT]; //----save storage
	u_int8_t 	vehicle_direction_list[VEHICULAR_AMOUNT]; //

	//added by wired
	int16_t		bs_id_list[VEHICULAR_AMOUNT];
	u_int8_t 	junc_row_prev_list[VEHICULAR_AMOUNT]; //
	u_int8_t 	junc_col_prev_list[VEHICULAR_AMOUNT]; //
	u_int8_t 	junc_row_next_list[VEHICULAR_AMOUNT]; //
	u_int8_t 	junc_col_next_list[VEHICULAR_AMOUNT]; //
};


#endif /* AVANET_TAVR_APP_H_ */
