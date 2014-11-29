#include <rayTracerCore/material.h>
#include <util/colors.h>
#include <stdio.h>

void printMaterial(const material mat)
{
    printf(KYEL"material[");
    printf(mat.reflect ? KBLU"reflect:"KGRN"TRUE " : KBLU"reflect:"KGRN"FALSE ");
    printf(KBLU"color:"KGRN"r:%4.4f g:%4.4f b:%4.4f"KYEL"]", mat.color[0],mat.color[1],mat.color[2]);
}