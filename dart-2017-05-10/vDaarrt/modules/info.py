'''
@auhtor : Corentin R
@date : February 2015

This file contains Info stuff. It represents the right part of the window where
other views of the robot are available

'''

from constantes import *
import pygame,pylygon
from pygame.locals import *
from numpy import array
import math

class Info :

    def __init__(self,sizeWorld) :
        self.sizeWorld = sizeWorld
        self.offsetX = self.sizeWorld[0]+10
        self.offsetY = elementSize
        self.myfont = pygame.font.SysFont("monospace", 16)
        self.author_display = self.myfont.render("Corentin Rifflart",1,(0,0,0))
        self.date_display = self.myfont.render("2015",1,(0,0,0))
        self.team_display = self.myfont.render("The Daarrt Team",1,(0,0,0))
        self.benblop_display = self.myfont.render("May 2016 : Modified by BenBlop",1,(0,0,0))
        self.cap_string = "Cap : "
        self.lSpeed_string = "Vitesse Gauche : "
        self.rSpeed_string = "Vitesse Droite : "
        self.logoImg = pygame.image.load(logo).convert_alpha()
        self.buttonImg = pygame.image.load(button).convert_alpha()



    def afficher(self,simu,daarrt2d,display) :
        '''
        return :
            void

        args :
            simu : pygame object
            daarrt2d : daarrt2d object
            display : type of display (int)

        draw the right part of the window (informations, views)

        '''
        pygame.draw.rect(simu,(0,0,0),(self.offsetX,self.offsetY,windowWidth-20,self.sizeWorld[1]/2),2)
        self.__afficherName(simu,daarrt2d)
        if (display == 0 or display ==1) :

            self.__afficherScale(simu,daarrt2d,display)
            self.__afficherClaw(simu,daarrt2d,display)


        if (display == 2 ):

            self.__afficherLogo(simu,daarrt2d,display)

        self.__afficherInfos(simu,daarrt2d)
        self.__afficherButton(simu)

    def __afficherInfos(self,simu,daarrt2d) :
        head = daarrt2d.robotHead
        simu.blit(self.myfont.render(self.cap_string+str(head),1,(0,0,0)),(self.offsetX,self.offsetY+self.sizeWorld[1]/2 +5))
        simu.blit(self.myfont.render(self.lSpeed_string+str(daarrt2d.leftSpeedCmd),1,(0,0,0)),(self.offsetX,self.offsetY+self.sizeWorld[1]/2 +20))
        simu.blit(self.myfont.render(self.rSpeed_string+str(daarrt2d.rightSpeedCmd),1,(0,0,0)),(self.offsetX,self.offsetY+self.sizeWorld[1]/2 +35))

    def __afficherButton(self,simu):

        simu.blit(self.buttonImg,(self.offsetX+10,self.sizeWorld[1]-60))

    def __afficherClaw(self,simu,daarrt2d,display) :

        if(display==0):

            pygame.draw.rect(simu,(0,255,0),(self.offsetX+70,self.offsetY+190-daarrt2d.clawHeight,10,10),1)
            pygame.draw.rect(simu,(0,255,0),(self.offsetX+80+daarrt2d.clawOpening,self.offsetY+190-daarrt2d.clawHeight,10,10),1)

        else :

            cap =- (daarrt2d.clawHeight+270)%360
            cap = cap*math.pi/180.0
            pygame.draw.line(simu,(255,0,0),(self.offsetX+50,self.offsetY+100),(self.offsetX+50+100*math.cos(cap),self.offsetY+100+100*math.sin(cap)),1)

    def __afficherLogo(self,simu,daarrt2d,display) :

        simu.blit(self.logoImg,(self.offsetX + 70 ,self.offsetY + 90 ))

    def __afficherScale(self,simu,daarrt2d,display) :

        pygame.draw.line(simu,(0,0,0),(self.offsetX+50,self.offsetY+10),(self.offsetX+50,self.offsetY+190),1)
        pygame.draw.line(simu,(0,0,0),(self.offsetX+40,self.offsetY+10),(self.offsetX+60,self.offsetY+10),1)
        pygame.draw.line(simu,(0,0,0),(self.offsetX+40,self.offsetY+190),(self.offsetX+60,self.offsetY+190),1)
        pygame.draw.line(simu,(0,0,0),(self.offsetX+40,self.offsetY+100),(self.offsetX+60,self.offsetY+100),1)

        simu.blit(self.myfont.render("180",1,(0,0,0)),(self.offsetX+5,self.offsetY))
        simu.blit(self.myfont.render("90",1,(0,0,0)),(self.offsetX+5,self.offsetY+90))
        simu.blit(self.myfont.render("0",1,(0,0,0)),(self.offsetX+5,self.offsetY+180))

        if(display == 0) :

            pygame.draw.line(simu,(0,0,0),(self.offsetX+80,self.offsetY+200),(self.offsetX+260,self.offsetY+200),1)

            pygame.draw.line(simu,(0,0,0),(self.offsetX+80,self.offsetY+190),(self.offsetX+80,self.offsetY+210),1)
            pygame.draw.line(simu,(0,0,0),(self.offsetX+170,self.offsetY+190),(self.offsetX+170,self.offsetY+210),1)
            pygame.draw.line(simu,(0,0,0),(self.offsetX+260,self.offsetY+190),(self.offsetX+260,self.offsetY+210),1)

            simu.blit(self.myfont.render("180",1,(0,0,0)),(self.offsetX+260,self.offsetY+210))
            simu.blit(self.myfont.render("90",1,(0,0,0)),(self.offsetX+170,self.offsetY+210))
            simu.blit(self.myfont.render("0",1,(0,0,0)),(self.offsetX+80,self.offsetY+210))

        else :
            pass

    def __afficherName(self,simu,daarrt2d):
        simu.blit(self.author_display, (self.offsetX+windowWidth-190, self.offsetY+self.sizeWorld[1]-100))
        simu.blit(self.date_display, (self.offsetX+windowWidth-190, self.offsetY+self.sizeWorld[1]-85))
        simu.blit(self.team_display, (self.offsetX+windowWidth-190, self.offsetY+self.sizeWorld[1]-70))
        simu.blit(self.benblop_display, (self.offsetX+windowWidth-320, self.offsetY+self.sizeWorld[1]-55))
