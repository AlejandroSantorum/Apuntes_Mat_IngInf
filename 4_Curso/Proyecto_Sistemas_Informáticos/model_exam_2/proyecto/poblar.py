import os
import django

os.environ.setdefault('DJANGO_SETTINGS_MODULE',
                      'proyecto.settings')
django.setup()

from aplicacion.models import Medico, Paciente, Receta


def populate():
    try:
        m1 = Medico.objects.get_or_create(id=1, nombre="medico1")[0]
        m1.save()
        m2 = Medico.objects.get_or_create(id=2, nombre="medico2")[0]
        m2.save()
        m3 = Medico.objects.get_or_create(id=3, nombre="medico3")[0]
        m3.save()
        m4 = Medico.objects.get_or_create(id=4, nombre="medico4")[0]
        m4.save()

        p1 = Paciente.objects.get_or_create(id=1, nombre="paciente1")[0]
        p1.save()
        p2 = Paciente.objects.get_or_create(id=2, nombre="paciente2")[0]
        p2.save()

        r1 = Receta.objects.get_or_create(id=1, medico=m1, paciente=p1)[0]
        r1.save()
        r2 = Receta.objects.get_or_create(id=2, medico=m2, paciente=p1)[0]
        r2.save()
        r3 = Receta.objects.get_or_create(id=3, medico=m1, paciente=p2)[0]
        r3.save()
        r4 = Receta.objects.get_or_create(id=4, medico=m2, paciente=p2)[0]
        r4.save()
        r5 = Receta.objects.get_or_create(id=5, medico=m3, paciente=p2)[0]
        r5.save()
    except Exceptions as e:
        print("ERROR: Something went wrong: ", str(e))
        exit()
    else:
        print("Todo ha ido bien")


# Start execution here!
if __name__ == '__main__':
    populate()
