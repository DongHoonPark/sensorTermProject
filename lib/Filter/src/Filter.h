class Filter
{
public:
	Filter();
	~Filter();
	void setsimplefiltererror(int e);
	int simplefilter(int x);
	void setkalman(float q, float r, float p);
	int kalman(int m);
	int simpleerror;
  int simplepast;
	float q;
	float r;
	float p;
	float v;
private:
	int count;
	float k;
};
