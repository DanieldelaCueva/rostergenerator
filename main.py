from env.env import *
from generator.generator import generate_pdf

import datetime

print("*************ROSTER GENERATOR*************")
context["competition"] = competicion = str(input("Competicion: "))
equipo = str(input("Equipo: "))
context["day"] = str(input("Jornada: "))
context["game_date"] = str(input("Fecha del partido: "))
context["game_time"] = str(input("Hora del partido: "))
context["generation_date"] = str(datetime.datetime.today().strftime('%d-%m-%Y %H:%M:%S'))
if equipo == "kdt":
    context["category"] = "CADETE FEMEMNINO C"
    p_list = player_list_kdt
    c_list = coach_list_kdt
    n = str(input("Eliminar jugadora... "))
    while n!="":
        to_delete = []
        for i in range(len(p_list)):
            if p_list[i]["num"] == n:
                to_delete.append(i)
        for index in to_delete:
            del p_list[index]
        n = str(input("Eliminar jugadora... "))

    n = str(input("Eliminar entrenador... "))
    while n!="":
        to_delete = []
        for i in range(len(c_list)):
            if c_list[i]["num"] == n:
                to_delete.append(i)
        for index in to_delete:
            del c_list[index]
        n = str(input("Eliminar entrenador... "))
    generate_pdf(context, p_list, c_list)
elif equipo == "inf":
    context["category"] = "INFANTIL FEMEMNINO C"
    p_list = player_list_inf
    c_list = coach_list_inf
    n = str(input("Eliminar jugadora... "))
    while n!="":
        to_delete = []
        for i in range(len(p_list)):
            if p_list[i]["num"] == n:
                to_delete.append(i)
        for index in to_delete:
            del p_list[index]
        n = str(input("Eliminar jugadora... "))

    n = str(input("Eliminar entrenador... "))
    while n!="":
        to_delete = []
        for i in range(len(c_list)):
            if c_list[i]["num"] == n:
                to_delete.append(i)
        for index in to_delete:
            del c_list[index]
        n = str(input("Eliminar entrenador... "))
    generate_pdf(context, p_list, c_list)