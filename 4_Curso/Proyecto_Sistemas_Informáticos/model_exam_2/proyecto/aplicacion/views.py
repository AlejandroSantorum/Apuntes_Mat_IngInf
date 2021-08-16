from django.shortcuts import render, redirect
from django.http import HttpResponse
from aplicacion.models import Medico, Paciente, Receta

# Create your views here.

def index(request):
    return HttpResponse("Examen final PSI - Alejandro Santorum")

def receta(request):
    context_dict = {}

    recetas = Receta.objects.all().order_by('-id')[:3]

    if recetas == None:
        context_dict['recetas'] = []
        context_dict['error'] = "No existen recetas actualmente"
    else:
        context_dict['recetas'] = recetas
        context_dict['error'] = None

    return render(request, "aplicacion/receta.html", context=context_dict)
