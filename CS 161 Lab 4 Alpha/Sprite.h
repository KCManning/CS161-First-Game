//-----------------------------------------------------------------------------
//Stores the sprite movement controls
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Moves sprite to the right, and has it face that direction
//-----------------------------------------------------------------------------
void sMoveRight()
{
	rectSprite.setF(1);
	if(rectSprite.getX() <= cintPNL_WIDTH - rectSprite.getW())
	{
		if(rectSprite.intersects(ground))
			rectSprite.setX(rectSprite.getX() + 10);
		else
			rectSprite.setX(rectSprite.getX() + 5);
	}
}

//-----------------------------------------------------------------------------
//Moves sprite to the left, and has it face that direction
//-----------------------------------------------------------------------------
void sMoveLeft()
{
	rectSprite.setF(NULL);
	if(rectSprite.getX() >= 0)
	{
		if(rectSprite.intersects(ground))
			rectSprite.setX(rectSprite.getX() - 10);
		else
			rectSprite.setX(rectSprite.getX() - 5);
	}
}

//-----------------------------------------------------------------------------
//Makes sprite jumps
//-----------------------------------------------------------------------------
void sJump()
{
	if(rectSprite.intersects(ground))
		rectSprite.setY(rectSprite.getY() - 100);
}

//-----------------------------------------------------------------------------
//Initiates sprite firing
//-----------------------------------------------------------------------------
void sShoot()
{
	if(shtAttack == 0)
		shtAttack = 2;
}

//-----------------------------------------------------------------------------
//Forces the player back to the ground
//-----------------------------------------------------------------------------
void sDrop()
{
	if(!rectSprite.intersects(ground))
		rectSprite.setY(rectSprite.getY() + 5);
}