from django.contrib import admin
from aplicacion.models import Medico, Paciente, Receta

# Register your models here.
admin.site.register(Medico)
admin.site.register(Paciente)
admin.site.register(Receta)
