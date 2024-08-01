class position
{
public:
	position(int xVal, int yVal) : x(xVal), y(yVal) {}

	int getX()
	{
		return x;
	}

	void setX(int x)
	{
		this->x = x;
	}

	int getY()
	{
		return y;
	}

	void setY(int y)
	{
		this->y = y;
	}

private:
	int x, y;
};