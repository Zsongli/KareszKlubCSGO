#pragma once
#include "Vector3.h"
#include "QAngle.h"
#include "Color.h"

enum class flag_t : int {
	on_ground = (1 << 0),
	ducking = (1 << 1),
	anim_ducking = (1 << 2),
	water_jump = (1 << 3),
	on_train = (1 << 4),
	in_rain = (1 << 5),
	frozen = (1 << 6),
	at_controls = (1 << 7),
	client = (1 << 8),
	fake_client = (1 << 9),
	in_water = (1 << 10),
	fly = (1 << 11),
	swin = (1 << 12),
	conveyor = (1 << 13),
	npc = (1 << 14),
	godmode = (1 << 15),
	no_target = (1 << 16),
	aim_target = (1 << 17),
	partial_ground = (1 << 18),
	static_prop = (1 << 19),
	graphed = (1 << 20),
	grenade = (1 << 21),
	step_movement = (1 << 22),
	dont_touch = (1 << 23),
	base_velocity = (1 << 24),
	world_brush = (1 << 25),
	object = (1 << 26),
	kill_me = (1 << 27),
	on_fire = (1 << 28),
	dissolving = (1 << 29),
	transragdoll = (1 << 30),
	unlockable_by_player = (1 << 31)
};

enum class movetype_t : int
{
	none = 0,
	isometric,
	walk,
	step,
	fly,
	flygravity,
	vphysics,
	push,
	noclip,
	ladder,
	observer,
	custom,
	last = custom,
	max_bits = 4
};

enum class teamnum_t : int {
	spec = 1, t, ct
};

class Entity {
public:
	union { // hogy a basetől induljon az összes offset
		struct {
			unsigned char _pad0[0x64]; // this + 0x64-nél van a client_id member
			int client_id;
		};
		struct {
			unsigned char _pad1[0x100]; // this + 0x100
			int health;
		};
		struct {
			unsigned char _pad2[0x108]; // this + 0x108
			Vector3 view_offset;
		};
		struct {
			unsigned char _pad3[0x138]; // this + 0x138
			Vector3 origin;
		};
		struct {
			unsigned char _pad4[0xED];
			bool is_dormant;
		};
		struct {
			unsigned char _pad5[0xF4];
			teamnum_t team;
		};
		struct {
			unsigned char _pad6[0x10488];
			int glow_index;
		};
		struct {
			unsigned char _pad7[0x93D];
			bool spotted;
		};
		struct {
			unsigned char _pad8[0x104];
			int flags;
		};
		struct {
			unsigned char _pad9[0x25C];
			movetype_t move_type;
		};
	};
	Vector3 get_eye_position();
	bool is_alive();
};

class LocalPlayer {
public:
	union {
		struct {
			unsigned char _pad0[0x64];
			int client_id;
		};
		struct {
			unsigned char _pad1[0x100];
			int health;
		};
		struct {
			unsigned char _pad2[0x108];
			Vector3 view_offset;
		};
		struct {
			unsigned char _pad3[0x138];
			Vector3 origin;
		};
		struct {
			unsigned char _pad5[0xF4];
			teamnum_t team;
		};
		struct {
			unsigned char _pad6[0x104];
			int flags;
		};
		struct {
			unsigned char _pad7[0x25C];
			movetype_t move_type;
		};
	};
	Vector3 get_eye_position();
	bool is_alive();
	QAngle get_view_angles();
	void set_view_angles(QAngle& angle);
	void aim_at(const Vector3& point);
};
