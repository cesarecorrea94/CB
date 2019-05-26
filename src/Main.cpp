/*
 * Main.cpp
 *
 *  Created on: 5 de ago de 2018
 *      Author: cesar
 */

#include "Main.hpp"

#include <stdlib.h>
#include <random>

int main(){
	alignmentMatrix oi
	//("elihC ed acilotaC dadisrevinU" ,"anirataC atnaS ed laredeF edadisrevinU");
	//("etnaruatseRsetnariM" ,"oiratisrevinUetnaruatseR");
	("u ed mos met a O" ,"uoy snoisnet tahW");
	//("CATAA", "GATACA");
	//("CGGCATTACTACTGATTACGTAGATGATCG", "ACGTACATGTCGTGCATTCTATCGAACTGA");
	//oi.global_comparison();
	oi.lcss_comparison();
	//oi.levenshtein_comparison();
	printf("%i", oi.similarity());
	puts(oi.print());
	//oi.printMatrix();
	return 0;
}

