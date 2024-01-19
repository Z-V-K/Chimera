#pragma once

namespace Colors
{
	namespace Notifications
	{
		const Color accent		{ 244, 175, 180, 255 };
		const Color background	{  45,  50,  80, 255 };
		const Color icon_shadow {  66,  71, 105, 255 };
	}

	namespace ChampionTracker 
	{
		const Color red			{ 226, 28, 52, 120 };
		const Color dark_red	{ 80, 11, 40, 200 };
	}

	namespace WardTracker
	{
		const Color wisteria			{ 189, 181, 213, 150 };
		const Color golden_yellow		{ 255, 192,   0, 255 };
		const Color cherry				{ 210,   4,  45, 255 };
		const Color rose				{ 243,  58, 106, 255 };
		const Color salmon				{ 250, 128, 144, 255 };
		const Color background			{   0,   0,   0, 120 };
		const Color background_timer	{   0,   0,   0, 200 };
		const Color ocean_blue			{ 103, 169, 250, 255 };
	}

	namespace SpellTracker
	{
		const Color stasis			{ 112, 128, 147, 255 };
		const Color dark_red		{ 255,   0,   0, 150 };
		const Color rudy			{ 255,	 0,	 40, 255 };
		const Color lime			{ 200, 236,  70, 255 };
		const Color drop_shadow		{	0,   0,   0, 150 };
		const Color pacific_blue	{  13, 165, 206, 255 };
		const Color exp_bar			{ 140, 90, 226, 255 };
		const Color exp_bar_bg		{ 20, 20, 20, 160 };

		namespace Legacy
		{
			const Color background			{   0,   0,   0, 180 };	// (background/border) black 70%
			const Color foreground			{ 120, 225, 120, 230 };	// (filling no cd) greenish
			const Color cooldown_font		{ 255, 255, 255, 255 };	// (cd font) white
			const Color level_indicator_dot	{   0,   0,   0, 255 };	// (level points) black
			const Color progressbar			{ 230, 145,  30, 255 };	// (progressbar) orange
		}

		namespace Modern
		{
			const Color border		{  68,  68, 68, 255 };	// grey
			const Color background	{  34,  31, 27, 255 };  // darker grey (shadow)
			const Color green		{ 124, 227,  9, 255 };	// green
			const Color red			{ 255,  27, 18, 255 };	// red
		}

		namespace LeagueHub
		{
			const Color level_indicator			{ 103, 169, 250, 255 };
			const Color background				{   0,   0,   0, 120 };
			const Color unleveled_background	{   0,   0,   0, 100 };
			const Color unleveled_border		{ 255, 255, 255,  70 };
		}
	}
}