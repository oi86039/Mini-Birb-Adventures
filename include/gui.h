#ifndef GUI_H
#define GUI_H

/**
*@brief Initialize Health, Energy, Opponent GUI
*/
void gui_setup_hud();

/**
*@brief Draw hud w/ current health params
*/
void gui_draw_hud();

/**
*@brief Set health of GUI bar
*@param health - value to set bar to (percentage)
*/
void gui_set_health(float health);

/**
*@brief Set energy of GUI bar
*@param energy - value to set bar to (percentage)
*/
void gui_set_energy(float energy);

/**
*@brief Set opponent health of GUI bar
*@param health - value to set bar to (percentage)
*/
void gui_set_opponent_health(float health);

#endif