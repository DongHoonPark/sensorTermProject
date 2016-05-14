class Speedcontrol
{
public:
	Speedcontrol();
	~Speedcontrol();
	void setSpeedcontrol(float basics, float linear, float curve, float slinear);
	float getSpeedcontrol(int sec, int cours, int cmax);
	float linear;
	float curve;
	float slinear;
	float basicspeed;
private:

};
