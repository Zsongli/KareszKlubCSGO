#pragma once
#include <windows.h>
#include "QAngle.h"
#include "entities.h"

class IClientEntityList { // source: source sdk 2013 github (csak a class definition)
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* get_client_networkable(int entnum) = 0;
	virtual void* get_client_networkable_from_handle(unsigned long handle) = 0;
	virtual void* get_client_unknown_from_handle(unsigned long handle) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual Entity* get_client_entity(int entnum) = 0;
	virtual Entity* get_client_entity_from_handle(unsigned long handle) = 0;

	// Returns number of entities currently in use
	virtual int					number_of_entities(bool include_non_networkable) = 0;

	// Returns highest index actually used
	virtual int					get_highest_entity_index(void) = 0;

	// Sizes entity list to specified size
	virtual void				set_max_entities(int max) = 0;
	virtual int					get_max_entities() = 0;
};

struct player_info {
	std::uint64_t	ullVersion = 0ULL;
	union {
		std::uint64_t ullXuid;

		struct {
			std::uint32_t nXuidLow;
			std::uint32_t nXuidHigh;
		};
	};

	char			szName[128];
	int				nUserID;
	char			szSteamID[33];
	std::uint32_t	nFriendsID;
	char			szFriendsName[128];
	bool			bFakePlayer;
	bool			bIsHLTV;
	int			uCustomFiles[4];
	std::uint8_t	dFilesDownloaded;
};

class IEngineClient {
private:
	virtual void _unused_0() = 0;
	virtual void _unused_1() = 0;
	virtual void _unused_2() = 0;
	virtual void _unused_3() = 0;
	virtual void _unused_4() = 0;
public:
	virtual void get_screen_size(int& width, int& height) = 0;
private:
	virtual void _unused_6() = 0;
	virtual void _unused_7() = 0;
public:
	virtual bool get_player_info(int index, player_info* info) = 0;
private:
	virtual void _unused_9() = 0;
	virtual void _unused_10() = 0;
public:
	virtual bool is_console_visible() = 0;
	virtual int get_local_player_index() = 0;
private:
	virtual void _unused_13() = 0;
public:
	virtual float get_last_time_stamp() = 0;
private:
	virtual void _unused_15() = 0;
	virtual void _unused_16() = 0;
	virtual void _unused_17() = 0;
public:
	virtual void get_view_angles(QAngle& angles) = 0;
	virtual void set_view_angles(QAngle& angles) = 0;
	virtual int get_max_clients() = 0;
private:
	virtual void _unused_21() = 0;
	virtual void _unused_22() = 0;
	virtual void _unused_23() = 0;
	virtual void _unused_24() = 0;
	virtual void _unused_25() = 0;
public:
	virtual bool is_in_game() = 0;
	virtual bool is_connected() = 0;
	virtual bool is_drawing_loading_image() = 0;
};

enum class glow_style_t : int
{
	default_style = 0,
	rimglow_3d,
	edge_highlight,
	edge_highlight_pulse,
	count
};

inline namespace interfaces {

	inline IClientEntityList* entity_list;
	inline IEngineClient* client_state;
	void* get_interface(const char* module, const char* name);
}
