#pragma once
class StageParams
{
	unsigned int windowWidth;
	unsigned int windowHight;
	unsigned int btnArea;
	unsigned int printIntervalMillis;

public:
	StageParams(unsigned int windowWidth = 500, unsigned int windowHight = 500, unsigned int btnArea = 100, unsigned int printIntervalMillis = 100);
	~StageParams();

	unsigned int getWindowWidth();
	unsigned int getWindowHight();
	unsigned int getBtnArea();
	unsigned int getPrintIntervalMillis();

	void setWindowWidth(unsigned int windowWidth);
	void setWindowHight(unsigned int windowHight);
	void setBtnArea(unsigned int btnAreaSize);
	void setPrintIntervalMillis(unsigned int printIntervalMillis);

};

