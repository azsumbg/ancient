#include "pch.h"
#include "ancient.h"

// RANDiT ****************************

dll::RANDiT::RANDiT()
{
	sq = new std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	twister = new std::mt19937{ *sq };
}

dll::RANDiT::~RANDiT()
{
	delete sq;
	delete twister;
}

int dll::RANDiT::operator() (int min, int max)
{
	std::uniform_int_distribution get_num{ min,max };
	return get_num(*twister);
}

//////////////////////////////////////

//PROTON ****************************

dll::PROTON::PROTON(float _sx, float _sy, float _width, float _height)
{
	start.x = _sx;
	start.y = _sy;

	width = _width;
	height = _height;

	end.x = start.x + width;
	end.y = start.y + height;
}
dll::PROTON::~PROTON() {};

float dll::PROTON::GetWidth() const
{
	return width;
}
float dll::PROTON::GetHeight() const
{
	return height;
}

void dll::PROTON::SetEdges()
{
	end.x = start.x + width;
	end.y = start.y + height;
}

void dll::PROTON::SetWidth(float _new_width)
{
	width = _new_width;
	SetEdges();
}
void dll::PROTON::SetHeight(float _new_height)
{
	height = _new_height;
	SetEdges();
}
void dll::PROTON::NewDims(float _new_width, float _new_height) 
{
	width = _new_width;
	height = _new_height;
	SetEdges();
}

//////////////////////////////////////

//CREATURE BASE ***********************

dll::CREATURE::CREATURE(float first_x, float first_y, uint8_t type) :PROTON(first_x, first_y)
{
	my_type = type;

	switch (my_type)
	{
	case hero_flag:
		NewDims(50.0f, 30.0f);
		my_speed = 5.0f;
		strenght = 10;
		lifes = 100;
		attack_delay = 100;
		max_frames = 11;
		frame_delay = 7;
		break;

	case evil1_flag:
		NewDims(20.0f, 50.0f);
		my_speed = 1.0f;
		strenght = 8;
		lifes = 80;
		attack_delay = 140;
		max_frames = 17;
		frame_delay = 4;
		break;

	case evil2_flag:
		NewDims(25.0f, 50.0f);
		my_speed = 1.1f;
		strenght = 9;
		lifes = 90;
		attack_delay = 180;
		max_frames = 13;
		frame_delay = 5;
		break;

	case evil3_flag:
		NewDims(40.0f, 60.0f);
		my_speed = 0.5f;
		strenght = 14;
		lifes = 120;
		attack_delay = 200;
		max_frames = 7;
		frame_delay = 10;
		break;

	case evil_med_flag:
		NewDims(30.0f, 60.0f);
		my_speed = 1.0f;
		strenght = 1;
		lifes = 50;
		attack_delay = 60;
		max_frames = 18;
		frame_delay = 4;
		break;
	}
}
dll::CREATURE::CREATURE(float first_x, float first_y, float end_x, float end_y) :PROTON(first_x, first_y, 10.0f, 15.0f)
{
	my_type = shot_flag;
	my_speed = 8.0f;
	max_frames = 7;
	frame_delay = 10;
	SetPathInfo(end_x, end_y);
}

dll::CREATURE::~CREATURE() {};

void dll::CREATURE::SetPathInfo(float to_where_x, float to_where_y)
{
	move_x = start.x;
	move_y = start.y;
	move_ex = to_where_x;
	move_ey = to_where_y;

	hor_line = false;
	vert_line = false;

	if (move_ex > move_x && move_ex - end.x <= 0)
	{
		vert_line = true;
		return;
	}
	else if (move_ex < move_x && move_ex - start.x <= 0)
	{
		vert_line = true;
		return;
	}
	else if (move_ex == move_x)
	{
		vert_line = true;
		return;
	}

	if (move_ey - start.y == 0 || move_ey - end.y == 0)
	{
		hor_line = true;
		return;
	}

	slope = (move_ey - move_y) / (move_ex - move_x);
	intercept = move_y - slope * move_x;
}

uint8_t dll::CREATURE::GetType() const
{
	return my_type;
}
void dll::CREATURE::SetType(uint8_t to_what)
{
	my_type = to_what;

	switch (my_type)
	{
	case hero_flag:
		NewDims(50.0f, 30.0f);
		my_speed = 5.0f;
		strenght = 10;
		lifes = 100;
		attack_delay = 100;
		max_frames = 11;
		frame_delay = 7;
		break;

	case evil1_flag:
		NewDims(20.0f, 50.0f);
		my_speed = 1.0f;
		strenght = 8;
		lifes = 80;
		attack_delay = 140;
		max_frames = 17;
		frame_delay = 4;
		break;

	case evil2_flag:
		NewDims(25.0f, 50.0f);
		my_speed = 1.1f;
		strenght = 9;
		lifes = 90;
		attack_delay = 180;
		max_frames = 13;
		frame_delay = 5;
		break;

	case evil3_flag:
		NewDims(40.0f, 60.0f);
		my_speed = 0.5f;
		strenght = 14;
		lifes = 120;
		attack_delay = 200;
		max_frames = 7;
		frame_delay = 10;
		break;

	case evil_med_flag:
		NewDims(30.0f, 60.0f);
		my_speed = 1.0f;
		strenght = 1;
		lifes = 50;
		attack_delay = 60;
		max_frames = 18;
		frame_delay = 4;
		break;
	}
}

int dll::CREATURE::GetFrame()
{
	--frame_delay;
	if (frame_delay <= 0)
	{	
		switch (my_type)
		{
		case hero_flag:
			frame_delay = 7;
			break;

		case evil1_flag:
			frame_delay = 4;
			break;

		case evil2_flag:
			frame_delay = 5;
			break;

		case evil3_flag:
			frame_delay = 10;
			break;

		case evil_med_flag:
			frame_delay = 4;
			break;
		
		case shot_flag:
			frame_delay = 10;
			break;
		}
		++frame;
		if (frame > max_frames)frame = 0;
	}

	return frame;
}
int dll::CREATURE::Attack()
{
	int damage = 0;
	--attack_delay;
	if (attack_delay <= 0)
	{
		switch (my_type)
		{
		case hero_flag:
			attack_delay = 100;
			break;

		case evil1_flag:
			attack_delay = 140;
			break;

		case evil2_flag:
			attack_delay = 180;
			break;

		case evil3_flag:
			attack_delay = 200;
			break;

		case evil_med_flag:
			attack_delay = 60;
			break;
		}
		damage = strenght;
	}
	return damage;
}
float dll::CREATURE::Distance(PROT_POINT my_point, PROT_POINT dest_point)
{
	float a = static_cast<float>(pow(abs(my_point.x - dest_point.x), 2));
	float b = static_cast<float>(pow(abs(my_point.y - dest_point.y), 2));

	return static_cast<float>(sqrt(a + b));
}

///////////////////////////////////////

//PROTON MESH *************************

dll::PROTON_MESH::PROTON_MESH(size_t num_of_elements) :max_size{ num_of_elements }, m_ptr{ new PROTON[num_of_elements] }
{
	for (size_t i = 0; i < max_size; ++i)*(m_ptr + i) = PROTON{};
}
dll::PROTON_MESH::~PROTON_MESH()
{
	if (m_ptr)delete[]m_ptr;
}

void dll::PROTON_MESH::push_back(PROTON& element)
{
	if (next_position + 1 <= max_size)
	{
		(*(m_ptr + next_position)) = element;
		++next_position;
	}
}
void dll::PROTON_MESH::remove(size_t index)
{
	if (index < next_position)
	{
		PROTON* temp_ptr{ new PROTON[next_position - 1] };

		for (size_t i = 0; i < next_position; ++i)
		{
			if (i != index)(*(temp_ptr + i)) = (*(m_ptr + i));
		}
		max_size = next_position - 1;
		delete[]m_ptr;
		m_ptr = temp_ptr;
	}
}
size_t dll::PROTON_MESH::capacity() const
{
	return max_size;
}
size_t dll::PROTON_MESH::size() const
{
	return next_position;
}

dll::PROTON& dll::PROTON_MESH::operator[](size_t index)
{
	static PROTON failed{};
	if (index < next_position)return(*(m_ptr + index));
	else return failed;
}
void dll::PROTON_MESH::operator()(size_t index, dll::PROTON& element)
{
	if (index < next_position)(*(m_ptr + index)) = element;
}

dll::PROTON& dll::PROTON_MESH::sort(PROT_POINT target)
{
	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (size_t i = 0; i < next_position - 1; ++i)
		{
			float a = static_cast<float>(pow(abs((*(m_ptr + i)).start.x - target.x), 2));
			float b = static_cast<float>(pow(abs((*(m_ptr + i)).start.y - target.y), 2));
			float distance1 = static_cast<float>(sqrt(a + b));
			
			a = static_cast<float>(pow(abs((*(m_ptr + i + 1)).start.x - target.x), 2));
			b = static_cast<float>(pow(abs((*(m_ptr + i + 1)).start.y - target.y), 2));
			float distance2 = static_cast<float>(sqrt(a + b));

			if (distance1 > distance2)
			{
				PROTON temp = (*(m_ptr + i));
				(*(m_ptr + i)) = (*(m_ptr + i + 1));
				(*(m_ptr + i + 1)) = temp;
				finished = false;
			}
		}
	}

	return (*(m_ptr));
}

///////////////////////////////////////

//SHOT ********************************

dll::SHOT::SHOT(float where_x, float where_y, float to_where_x, float to_where_y) 
	:CREATURE(where_x, where_y, to_where_x, to_where_y) {};

bool dll::SHOT::Move(float gear, float targ_x, float targ_y)
{
	float now_speed = my_speed + gear / 10.0f;
	
	if (vert_line)
	{
		if (start.y < move_ey)
		{
			start.y += now_speed;
			SetEdges();
			if (end.y <= ground)return true;
			else return false;
		}
		else if (start.y > move_ey)
		{
			start.y -= now_speed;
			SetEdges();
			if (start.y >= sky)return true;
			else return false;
		}
		else return false;
	}
	if (hor_line)
	{
		if (start.x < move_ex)
		{
			start.x += now_speed;
			SetEdges();
			if (end.x <= scr_width)return true;
			else return false;
		}
		else if (start.x > move_ex)
		{
			start.x -= now_speed;
			SetEdges();
			if (start.x >= 0)return true;
			else return false;
		}
		else return false;
	}

	if (start.x < move_ex)
	{
		start.x += now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (end.x <= scr_width)return true;
		else return false;
	}
	else if (start.x > move_ex)
	{
		start.x -= now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (start.x >= 0)return true;
		else return false;
	}

	return false;
}
dll::PROT_POINT dll::SHOT::AINextMove(PROTON_MESH& army, float hero_x, float hero_y)
{
	return PROT_POINT{ start.x,sky };
	
}
void dll::SHOT::Release()
{
	delete this;
}

///////////////////////////////////////


// EVIL ******************************

dll::EVIL::EVIL(uint8_t type, float where_x, float where_y) :CREATURE(where_x, where_y, type) {};

bool dll::EVIL::Move(float gear, float targ_x, float targ_y)
{
	float now_speed = my_speed + gear / 10.0f;
	SetPathInfo(targ_x, targ_y);

	if (vert_line)
	{
		if (start.y < targ_y)
		{
			start.y += now_speed;
			SetEdges();
			if (end.y <= ground)return true;
			else return false;
		}
		else if (start.y > targ_y)
		{
			start.y -= now_speed;
			SetEdges();
			if (start.y >= sky)return true;
			else return false;
		}
		else return false;
	}
	if (hor_line)
	{
		if (start.x < targ_x)
		{
			start.x += now_speed;
			SetEdges();
			if (end.x <= scr_width)return true;
			else return false;
		}
		else if (start.x > targ_x)
		{
			start.x -= now_speed;
			SetEdges();
			if (start.x >= 0)return true;
			else return false;
		}
		else return false;
	}

	if (start.x < targ_x)
	{
		start.x += now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (end.x <= scr_width)return true;
		else return false;
	}
	else if (start.x > targ_x)
	{
		start.x -= now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (start.x >= 0)return true;
		else return false;
	}
	
	return false;
}
dll::PROT_POINT dll::EVIL::AINextMove(PROTON_MESH& army, float hero_x, float hero_y)
{
	for (size_t i = 0; i < army.size(); ++i)
	{
		if (abs(army[i].start.x - hero_x) <= 150 && abs(army[i].start.y - hero_y) <= 150)return PROT_POINT{ hero_x,hero_y };
		else
		{
			if (army[i].start.x < hero_x)return PROT_POINT{ army[i].start.x + (float)(class_rand(20, 100)),ground };
			else if (army[i].start.x > hero_x)return PROT_POINT{ army[i].start.x - (float)(class_rand(20,100)), ground };
			else return PROT_POINT{ army[i].start.x, ground };
		}
	}

	return PROT_POINT{ 0,0 };
}
void dll::EVIL::Release()
{
	delete this;
}

/////////////////////////////////////

// HERO ****************************

dll::HERO::HERO(float where_x, float where_y) :CREATURE(where_x, where_y, hero_flag) {};

bool dll::HERO::Move(float gear, float targ_x, float targ_y)
{
	float now_speed = my_speed + gear / 10.0f;
	SetPathInfo(targ_x, targ_y);

	if (vert_line)
	{
		if (start.y < targ_y)
		{
			start.y += now_speed;
			SetEdges();
			if (end.y <= ground)return true;
			else return false;
		}
		else if (start.y > targ_y)
		{
			start.y -= now_speed;
			SetEdges();
			if (start.y >= sky)return true;
			else return false;
		}
		else return false;
	}
	if (hor_line)
	{
		if (start.x < targ_x)
		{
			start.x += now_speed;
			SetEdges();
			if (end.x <= scr_width)return true;
			else return false;
		}
		else if (start.x > targ_x)
		{
			start.x -= now_speed;
			SetEdges();
			if (start.x >= 0)return true;
			else return false;
		}
		else return false;
	}

	if (start.x < targ_x)
	{
		start.x += now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (end.x <= scr_width)return true;
		else return false;
	}
	else if (start.x > targ_x)
	{
		start.x -= now_speed;
		start.y = start.x * slope + intercept;
		SetEdges();
		if (start.x >= 0)return true;
		else return false;
	}

	return false;
	
}
dll::PROT_POINT dll::HERO::AINextMove(PROTON_MESH& army, float hero_x, float hero_y)
{
	return PROT_POINT{ hero_x, hero_y };
}
void dll::HERO::Release()
{
	delete this;
}

////////////////////////////////////

// FACTORIES ************************

dll::Object dll::CreatureFactory(float sx, float sy, uint8_t what_type)
{
	Object ret = nullptr;

	if (what_type == hero_flag)ret = new HERO(sx, sy);
	else ret = new EVIL(what_type, sx, sy);
	return ret;

}
dll::Object dll::ShotFactory(float sx, float sy, float ex, float ey)
{
	return new dll::SHOT(sx, sy, ex, ey);
}