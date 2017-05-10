# -*- coding: utf-8 -*-
"""
Created on Thu May 19 14:56:15 2016

@author: newubu
"""

# world for DART challenge uses walls to define world1.txt
# put the robot at the start of the track

import constantes
import world
import geometry
import Image
myWorld=world.World(constantes.worldName)
elsz=myWorld.elementSize

img = Image.open("../data/mur30.png")
img = img.resize((elsz,elsz),Image.ANTIALIAS)
img.save("../data/mur.png",quality=50)


nCase=(5*constantes.panelSize)/elsz
nLine=(3*constantes.panelSize)/elsz
tply = geometry.createWall(myWorld,nCase,nLine)


grid = [['x']*(nLine) for i in range(nCase)]

i=0
for ply in tply:
    i += 1
    ix0,iy0=ply[0]/elsz
    ix1,iy1=ply[2]/elsz
    for ix in range(ix1-ix0):
        for iy in range(iy1-iy0):
            grid[ix+ix0][iy+iy0] = 'M'

#fgrid = open(constantes.worldName,"w")
fgrid = open("../../"+constantes.worldName,"w")
for iy in range(nLine):
    for ix in range(nCase):
        if (ix == 10) and (iy == ((1*nLine)/4)):
            fgrid.write ("%c"%('D'))
        else:
            fgrid.write ("%c"%(grid[ix][iy]))
    if iy == (nLine-2):
        fgrid.write ("L")
    fgrid.write("\n")
        
fgrid.close()
    
