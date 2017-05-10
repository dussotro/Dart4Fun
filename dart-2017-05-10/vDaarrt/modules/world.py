'''
@auhtor : Corentin R
@date : February 2015

This file contains world generation stuff.
It loads a .txt file and generates a structure understable by the program.

'''



import time, math, sys
import pygame,pylygon
from pygame.locals import *
from numpy import array
import math
import os
import geometry as geo

from constantes import *


class World :

    def __init__(self,fichier):
        self.nom = fichier
        self.structure = 0
        self.obstacle = []
        self.numberCase = 0
        self.numberLine = 0
        self.elementSize = elementSize
        print elementSize

    def generer(self):

        """
        return a list containing lenght and width for the windows

        args :
            void

        generate a world from a .txt file. The path must be indicated in
        constantes.py

        """
        num_case = 0
        num_line = 0
        print self.nom
        with open(self.nom,"r") as fichier :

            structure_monde = []
            for line in fichier :

                line_monde = []
                for element in line :

                    if element != '\n':

                        line_monde.append(element)
                        num_case += 1
                        if element == 'L':

                            num_case = 0

                structure_monde.append(line_monde)
                num_line += 1

            self.structure = structure_monde
            #num_line -= 2

        print num_case,num_line
        self.numberCase = num_case
        self.numberLine = num_line
        self.obstacle = geo.createWall(self,self.numberCase,self.numberLine)

        return [self.numberCase*self.elementSize , self.numberLine*self.elementSize]


    def afficher(self,simulation,initiate):

        """
        no return

        args :
            simulation : pygame object
            initiate : boolean, true if it is the first call, false otherwise

        draw the world in the pygame object

        """

        num_line = 0
        compteur = 0
        myWall = pygame.image.load(mur).convert_alpha()
        myObstacle = pygame.image.load(obstacle).convert_alpha()
        for ligne in self.structure :

            num_case = 0
            for element in ligne :

                x = num_case*elementSize
                y = num_line*elementSize
                if element == 'M':

                    simulation.blit(myWall,(x,y))

                elif element == 'O':

                    simulation.blit(myObstacle,(x,y))
                    if( initiate == True ):

                        self.obstacle.append(geo.createObstacle(self,x,y))

                elif element == 'D' :
                    daarrtpos=[x,y]
                num_case += 1

            num_line += 1
        try :
            return daarrtpos
        except : return [250.0,250.0]
