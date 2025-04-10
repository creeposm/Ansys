#include "udf.h"
#include "sg.h"
#include "mem.h"
#include "stdio.h"
#include "string.h"

/* Define number of species manually */
#define NUM_SPECIES 5
#define MAX_SPECIES_NAME_LEN 32

DEFINE_ON_DEMAND(check_phase2_species)
{
    Domain *mixture_domain;
    Domain *phase_domain;
    Thread *phase_thread = NULL;
    int i, phase_id = 1;
    Thread *t;

    char species_names[NUM_SPECIES][MAX_SPECIES_NAME_LEN];

    strcpy(species_names[0], "O2");
    strcpy(species_names[1], "CO[NH2]2");
    strcpy(species_names[2], "HNCO");
    strcpy(species_names[3], "NH3");
    strcpy(species_names[4], "H2O");

    mixture_domain = Get_Domain(1);
    if (mixture_domain == NULL) {
        printf("Error: Mixture domain not found!\n");
        return;
    }

    phase_domain = DOMAIN_SUB_DOMAIN(mixture_domain, phase_id);
    if (phase_domain == NULL) {
        printf("Error: Secondary phase domain not found!\n");
        return;
    }

    /* Search for any valid thread in the phase domain */
    thread_loop_c(t, phase_domain)
    {
        phase_thread = t;
        break;
    }

    if (phase_thread == NULL) {
        printf("Error: Phase thread not found!\n");
        return;
    }

    printf("\nSpecies in Phase %d:\n", phase_id);
    printf("%-5s %-30s\n", "Index", "Name");
    printf("----------------------------------\n");

    for (i = 0; i < NUM_SPECIES; i++) {
        printf("%-5d %-30s\n", i, species_names[i]);
    }

    printf("----------------------------------\n");
}
