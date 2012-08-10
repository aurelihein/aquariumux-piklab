/**
 * \file aquarium.h
 * \brief Main functions of aquarium cycles
 * \author Aurelien BOUIN
 * \version 1.0.0
 * \date 09 august 2012
 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 2012  Aurelien BOUIN (a_bouin@yahoo.fr)                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This program is free software; you can redistribute it and/or              *
 *  modify it under the terms of the GNU General Public License                *
 *  as published by the Free Software Foundation; either version 3             *
 *  of the License, or (at your option) any later version.                     *
 *                                                                             *
 *  This program is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *  GNU General Public License for more details.                               *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License          *
 *  along with this program; if not, write to the Free Software                *
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef enum {INIT_REMPLISSAGE = 0, REMPLISSAGE_EAU_OSMOSEE, FIN_EAU_OSMOSEE, REMPLISSAGE_EAU_SOURCE, FIN_EAU_SOURCE, FIN_REMPLISSAGE} remplissage_states;
typedef enum {INIT_VIDAGE = 0, DEBUT_VIDAGE, VIDAGE, FIN_VIDAGE, ATTENTE_PROCHAIN_CYCLE_VIDAGE} vidage_states;

#define TEMPO_ALLUMAGE_VIDAGE		(10)	//en secondes
#define TEMPO_ATTENTE_ENTRE_VIDAGE	(120)	//en secondes

//entrees
char get_capteur_niveau_vide(void);
char get_capteur_niveau_eau_osmosee(void);
char get_capteur_niveau_plein(void);

//sorties
void set_electrovanne_eau_osmosee(char state);
void set_prise_electrique_eau_source(char state);
void set_prise_electrique_vidage(char state);

void init_aquarium_state(void);
void test_add_cycle (void);
int cycle_vidage(void);
int cycle_remplissage(void);
void incremente_tempo(void);
void update_output_cycle_remplissage(void);
void update_output_cycle_vidage(void);




