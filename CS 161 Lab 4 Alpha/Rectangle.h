//-----------------------------------------------------------------------------
//Defines the rectangle class
//-----------------------------------------------------------------------------
#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace cRectangle
{
	class CRectangle

	{
	public:
		CRectangle(short x1 = 0, short y1 = 0, short w1 = 0, short h1 = 0, short f1 = 0, short health = 0)
		{
			setX(x1);
			setY(y1);
			setW(w1);
			setH(h1);
			setF(f1);
			setHealth(health);
		}

		short getX(){return x;}

		void setX(short x1){x = x1;}

		short getY(){return y;}

		void setY(short y1){y = y1;}

		short getW(){return w;}

		void setW(short w1){w = w1;}

		short getH(){return h;}

		void setH(short h1){h = h1;}

		short getF(){return f;}

		void setF(short f1){f = f1;}

		short getHealth(){return m_health;}

		void setHealth(short health){m_health = health;}

		bool intersects(CRectangle rect)
		{
			if((rect.getX() + rect.getW() > x) && (rect.getX() < x + w) &&
				(rect.getY() + rect.getH() > y) && (rect.getY() < y + h))
				return true;
			else
				return false;
		}

	private:
		short x;
		short y;
		short w;
		short h;
		short f;
		short m_health;
	};

}
#endif