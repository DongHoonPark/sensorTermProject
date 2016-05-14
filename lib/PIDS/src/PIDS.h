class PIDS
{
public:
	PIDS();
	~PIDS();
	void setPIDS(float kp, float ki, float dt, float ermax, float steer_v);
	float getPIDS(int vec);
	float dt;
	float Kp;
	float Ki;
	float ermax;
	float steer_v;
private:
	float Kp_v;
	float Ki_v;
	float error_int;
};
