#include "aquarium.h"

#include "serial.h"
#include "stdio.h"

#define printf	serial_puts

//entrees
char capteur_niveau_vide = 1;
char capteur_niveau_eau_osmosee = 0;
char capteur_niveau_plein = 0;

//sorties
int tempo_allumage_vidage = 0;
int tempo_attente_entre_vidage = 0;

//1 remplissage automatique activée
char remplissage_auto = 1;

remplissage_states remplissage_state;
vidage_states vidage_state;

#ifdef	TEST
	int cycle = 0;

void init_aquarium_state(void)
{
    remplissage_state = INIT_REMPLISSAGE;
    vidage_state = INIT_VIDAGE;
}
	
void add_cycle (void){
	if(cycle == 1)		capteur_niveau_vide=0;
	if(cycle == 10)	capteur_niveau_eau_osmosee=1;
	if(cycle == 30)	capteur_niveau_plein=1;
	if(cycle == 300)	return -1;
	cycle_remplissage();
	cycle_vidage();
	incremente_tempo();
}
#endif

void printf_remplissage_state(remplissage_states s){
	switch(s)
	{
		case INIT_REMPLISSAGE :
			printf("REMPLISSAGE:INIT_REMPLISSAGE\r\n");
		break;
		case REMPLISSAGE_EAU_OSMOSEE :
			printf("REMPLISSAGE:REMPLISSAGE_EAU_OSMOSEE\r\n");
		break;
		case FIN_EAU_OSMOSEE :
			printf("REMPLISSAGE:FIN_EAU_OSMOSEE\r\n");
		break;
		case REMPLISSAGE_EAU_SOURCE :
			printf("REMPLISSAGE:REMPLISSAGE_EAU_SOURCE\r\n");
		break;
		case FIN_EAU_SOURCE :
			printf("REMPLISSAGE:FIN_EAU_SOURCE\r\n");
		break;
		case FIN_REMPLISSAGE :
			printf("REMPLISSAGE:FIN_REMPLISSAGE\r\n");
		break;
		default :
			printf("REMPLISSAGE:UNKNOW_REMPLISSAGE_STATE\r\n");
		break;
	}
}

void printf_vidage_state(vidage_states s){
	switch(s)
	{
		case INIT_VIDAGE :
			printf("VIDAGE:INIT_VIDAGE\r\n");
		break;
		case DEBUT_VIDAGE :
			printf("VIDAGE:DEBUT_VIDAGE\r\n");
		break;
		case VIDAGE :
			printf("VIDAGE:VIDAGE\r\n");
		break;
		case FIN_VIDAGE :
			printf("VIDAGE:FIN_VIDAGE\r\n");
		break;
		case ATTENTE_PROCHAIN_CYCLE_VIDAGE :
			printf("VIDAGE:ATTENTE_PROCHAIN_CYCLE_VIDAGE\r\n");
		default :
			printf("VIDAGE:UNKNOW_VIDAGE_STATE\r\n");
		break;
	}
}


char get_capteur_niveau_vide(void){
	return capteur_niveau_vide;
}
char get_capteur_niveau_eau_osmosee(void){
	return capteur_niveau_eau_osmosee;
}
char get_capteur_niveau_plein(void){
	return capteur_niveau_plein;
}

void set_electrovanne_eau_osmosee(char state){
    if(state)
	printf("TURN ON:eau_osmosee\r\n");
    else
	printf("TURN OFF:eau_osmosee\r\n");
}
void set_prise_electrique_eau_source(char state){
    if(state)
	printf("TURN ON:eau_source\r\n");
    else
	printf("TURN OFF:eau_source\r\n");
}
void set_prise_electrique_vidage(char state){
    if(state)
	printf("TURN ON:vidage\r\n");
    else
	printf("TURN OFF:vidage\r\n");
}

void incremente_tempo(void){
	tempo_allumage_vidage++;
	tempo_attente_entre_vidage++;
	printf("TICK\r\n");
	//printf("tempo_allumage_vidage:%d, tempo_attente_entre_vidage:%d\n",tempo_allumage_vidage,tempo_attente_entre_vidage);
}

void update_output_cycle_remplissage(void){
	printf_remplissage_state(remplissage_state);
	switch(remplissage_state)
	{
		case INIT_REMPLISSAGE :
			//rien
		break;
		case REMPLISSAGE_EAU_OSMOSEE :
			set_electrovanne_eau_osmosee(1);
		break;
		case FIN_EAU_OSMOSEE :
			set_electrovanne_eau_osmosee(0);
		break;
		case REMPLISSAGE_EAU_SOURCE :
			set_prise_electrique_eau_source(1);
		break;
		case FIN_EAU_SOURCE :
			set_prise_electrique_eau_source(0);
		break;
		case FIN_REMPLISSAGE :
			//rien
		break;
		default :
		break;
	}
}

void update_output_cycle_vidage(void){
	printf_vidage_state(vidage_state);
	switch(vidage_state)
	{
		case INIT_VIDAGE :
			//rien
		break;
		case DEBUT_VIDAGE :
			tempo_allumage_vidage = 0;
			set_prise_electrique_vidage(1);
		break;
		case VIDAGE :
			//rien
		break;
		case FIN_VIDAGE :
			set_prise_electrique_vidage(0);
			tempo_attente_entre_vidage = 0;
		break;
		case ATTENTE_PROCHAIN_CYCLE_VIDAGE :
			//rien
		break;
		default :
		break;
	}
}

int cycle_remplissage(void){
	int update_cycle = 0;
	switch(remplissage_state)
	{
		case INIT_REMPLISSAGE :
			if(get_capteur_niveau_vide() && !get_capteur_niveau_eau_osmosee() && !get_capteur_niveau_plein()){
				remplissage_state = REMPLISSAGE_EAU_OSMOSEE;
				update_cycle = 1;
			}
		break;
		case REMPLISSAGE_EAU_OSMOSEE :
			if(get_capteur_niveau_eau_osmosee()){
				remplissage_state = FIN_EAU_OSMOSEE;
				update_cycle = 1;
			}
		break;
		case FIN_EAU_OSMOSEE :
			if(1){
				remplissage_state = REMPLISSAGE_EAU_SOURCE;
				update_cycle = 1;
			}
		break;
		case REMPLISSAGE_EAU_SOURCE :
			if(get_capteur_niveau_plein()){
				remplissage_state = FIN_EAU_SOURCE;
				update_cycle = 1;
			}
		break;
		case FIN_EAU_SOURCE :
			if(remplissage_auto){
				remplissage_state = INIT_REMPLISSAGE;
				update_cycle = 1;
			}else{
				remplissage_state = FIN_REMPLISSAGE;
				update_cycle = 1;
			}
		break;
		case FIN_REMPLISSAGE :
			//rien
		break;
		default :
		break;
	}
	if(update_cycle)
		update_output_cycle_remplissage();
	return 0;
}

int cycle_vidage(void){
	int update_cycle = 0;
	switch(vidage_state)
	{
		case INIT_VIDAGE :
			if(!capteur_niveau_vide && (remplissage_state==INIT_REMPLISSAGE) ){
				vidage_state = DEBUT_VIDAGE;
				update_cycle = 1;
			}
		break;
		case DEBUT_VIDAGE :
			if(1){
				vidage_state = VIDAGE;
				update_cycle = 1;
			}
		break;
		case VIDAGE :
			if(capteur_niveau_vide || (tempo_allumage_vidage >= TEMPO_ALLUMAGE_VIDAGE) ){
				vidage_state = FIN_VIDAGE;
				update_cycle = 1;
			}
		break;
		case FIN_VIDAGE :
			if(capteur_niveau_vide){
				vidage_state = INIT_VIDAGE;
			}else{
				vidage_state = ATTENTE_PROCHAIN_CYCLE_VIDAGE;
			}
			update_cycle = 1;
		break;
		case ATTENTE_PROCHAIN_CYCLE_VIDAGE :
			if(tempo_attente_entre_vidage >= TEMPO_ATTENTE_ENTRE_VIDAGE){
				vidage_state = INIT_VIDAGE;
				update_cycle = 1;
			}
		break;
		default :
		break;
	}
	if(update_cycle)
		update_output_cycle_vidage();
	return 0;
}
