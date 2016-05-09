//Elijah Davis
//cs 335
//started 4/22/16
//screen transitions and collision detection of player
//and bullets with each other, the walls, and objects
#include <iostream>
#include "main.h"
#include "miguelT.h"
using namespace std;
//used when player collides with wall to shift to new tile
void shiftScreen(Game *game, char direction)
{
	if (direction == 'u') {
		game->map[1]++;
	}
	if (direction == 'd') {
		game->map[1]--;
	}
	if (direction == 'l') {
		game->map[0]--;
	}
	if (direction == 'r') {
		game->map[0]++;
	}
	std::cout << game->map[0]  << ", " << game->map[1] << endl;
	initEnemies(game);
}
void Player_Object(Game *game, Player *p)
{
	p = & game->player;
	//defined edges
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;
	
	Shape *s;
	for (int i = 0; i < game->num_objects; i++) {
		s = &game->object[i];
		
		if (top >= s->center.y - s->height
		&& top <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y > 0 ) {
			p->velocity.y = 0;
			p->s.center.y -= top -  (s->center.y -s->height);
		}
		if (bot >= s->center.y - s->height
		&& bot <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y < 0 ) {
			p->velocity.y = 0;
			p->s.center.y -= bot -  (s->center.y + s->height);
		}
		if (left >= s->center.x - s->width
		&& left <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x < 0 ) {
			p->velocity.x = 0;
			p->s.center.x -= left -  (s->center.x + s->width);
		} 
		if (right >= s->center.x - s->width
		&& right <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x > 0 ) {
			p->velocity.x = 0;
			p->s.center.x -= right -  (s->center.x - s->width);
		} 
	}
}
void playerCollision(Game *game)
{
	Player *p;
	p = &game->player;
	//defined edges
	float top = p->s.center.y  + p->s.height;
	float bot = p->s.center.y  - p->s.height;
	float left = p->s.center.x - p->s.width;
	float right = p->s.center.x + p->s.width;

	//detect object collisions 
	Player_Object(game, &game->player);
	/*Shape *s;
	for (int i = 0; i < game->num_objects; i++) {
		s = &game->object[i];

		if (top >= s->center.y - s->height
		&& top <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y > 0 ) {
			p->velocity.y = 0;
		} 
		
		if (bot >= s->center.y - s->height
		&& bot <= s->center.y + s->height
		&& left < s->center.x + s->width
		&& right > s->center.x - s->width
		&& p->velocity.y < 0 ) {
			p->velocity.y = 0;
		} 
		if (left >= s->center.x - s->width
		&& left <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x < 0 ) {
			p->velocity.x = 0;
		} 
		if (right >= s->center.x - s->width
		&& right <= s->center.x + s->width
		&& bot < s->center.y + s->height
		&& top > s->center.y - s->height
		&& p->velocity.x > 0 ) {
			p->velocity.x = 0;
		} 
		
	}*/
	//detect screen collisions
	//floor
	if (bot <= 0 && p->velocity.y < 0) {
		p->s.center.y = WINDOW_HEIGHT - p->s.height;
		//change when multiple weapons implemented
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'd');
	}
	//roof
	if (top >= WINDOW_HEIGHT && p->velocity.y > 0) {
		p->s.center.y = p->s.height;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'u');
	}
	//left wall
	if (left <= 0 && p->velocity.x < 0) {
		p->s.center.x = WINDOW_WIDTH - p->s.width;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'l');
	}
	//right wall
	if (right >= WINDOW_WIDTH && p->velocity.x > 0) {
		p->s.center.x = p->s.width;
		//
		game->knife.k.center.x = p->s.center.x + 20;
		game->knife.k.center.y = p->s.center.y +5;
		//
		shiftScreen(game, 'r');
	}
	//player-enemy collision
	for ( int i = 0; i < 5/*game->num_enemies*/; i++) {
		Player *e;
		e = &game->enemies[i];	
		float enemy_b = 
			e->s.center.y - e->s.height;
		float enemy_t = 
			e->s.center.y + e->s.height;
		float enemy_l = 
			e->s.center.x - e->s.width;
		float enemy_r = 
			e->s.center.x + e->s.width;
		if (top >= enemy_b &&
		bot <= enemy_t &&
		left <= enemy_r &&
		right >= enemy_l) {
		//knocked back when hit enemy
			/*for (int j = 0; j < num_objects; j++) {
				if (top - (game->object[j].center.x - game->object[j].height) < (p->s.center.y - e->s.center.y)
			*/
			p->s.center.x += (p->s.center.x - e->s.center.x);
			e->s.center.x -= (p->s.center.x - e->s.center.x);
			e->velocity.x *= -1;
			p->s.center.y += (p->s.center.y - e->s.center.y);
			e->s.center.y -= (p->s.center.y - e->s.center.y);
			e->velocity.y *= -1;	
		}
	}
			
	
}
void particleCollision(Game *game) 
{
	Player *play;
	play = &game->player;
	float top = play->s.center.y  + play->s.height;
	float bot = play->s.center.y  - play->s.height;
	float left = play->s.center.x - play->s.width;
	float right = play->s.center.x + play->s.width;
	
	Particle *p;
	Shape *s;
	
	for (int i = 0; i < game->n; i++) {
		p = &game->particle[i];
		//check for bullet collision with player
		if (p->s.center.x > bot
		&& p->s.center.x < top
		&& p->s.center.y >left	
		&& p->s.center.y < right) {
			*p = game->particle[game->n-1];
			game->n--;
			play->health--;
		}
			
		//check for bullet collisions with enemies
		for (int j = 0; j < 5/*game->num_enemies*/; j++) {
			Player *e = &game->enemies[j];
			float botE = e->s.center.y - e->s.height;
			float topE = e->s.center.y  + e->s.height;
			float leftE = e->s.center.x - e->s.width;
			float rightE = e->s.center.x + e->s.width;

			if (p->s.center.y > botE
			&& p->s.center.y < topE
			&& p->s.center.x >leftE	
			&& p->s.center.x < rightE) {
				*p = game->particle[game->n-1];
				game->n--;
				e->health--;
		
			}
		}
		//check for bullet collision with enviornment
		for (int j = 0; j < game->num_objects; j++) {
			s = &game->object[j];
			
			if (p->s.center.x <= s->center.x + s->width
			&& p->s.center.x >= s->center.x - s->width
			&& p->s.center.y <= s->center.y 	+ s->height
			&& p->s.center.y >= s->center.y - s->height) {
				*p = game->particle[game->n-1];
				game->n--;
				cout << "hit a wall" << endl;
				break;
			}
		}
		//check for off-screen
		if (p->s.center.x > WINDOW_WIDTH + p->s.width) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.x < 0.0) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y > WINDOW_HEIGHT + p->s.height) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
		if (p->s.center.y < 0.0) {
			std::cout << "off screen" << std::endl;
			game->particle[i] = game->particle[game->n-1];
			game->n--;
		}
	
	}
}
