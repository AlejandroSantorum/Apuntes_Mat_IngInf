from django.test import TestCase
from aplicacion.models import Medico, Paciente, Receta
from django.test import Client
from django.urls import reverse
import re

# Create your tests here.

class ExamenTests(TestCase):

    def setUp(self):
        self.client = Client()

    @classmethod
    def decode(cls, txt):
        return txt.decode("utf-8")

    def test1(self):
        Receta.objects.all().delete()
        Medico.objects.all().delete()
        Paciente.objects.all().delete()

        m1 = Medico.objects.get_or_create(id=1, nombre="medico1")[0]
        m1.save()

        p1 = Paciente.objects.get_or_create(id=1, nombre="paciente1")[0]
        p1.save()

        r1 = Receta.objects.get_or_create(id=1, medico=m1, paciente=p1)[0]
        r1.save()
        r2 = Receta.objects.get_or_create(id=2, medico=m1, paciente=p1)[0]
        r2.save()
        r3 = Receta.objects.get_or_create(id=3, medico=m1, paciente=p1)[0]
        r3.save()
        r4 = Receta.objects.get_or_create(id=4, medico=m1, paciente=p1)[0]
        r4.save()

        response = self.client.get(reverse('receta'))
        m = re.search(r"<th>4</th>\n *<td>paciente1</td>\n *<td>medico1</td>", self.decode(response.content))
        self.assertTrue(m)
        m = re.search(r"<th>3</th>\n *<td>paciente1</td>\n *<td>medico1</td>", self.decode(response.content))
        self.assertTrue(m)
        m = re.search(r"<th>2</th>\n *<td>paciente1</td>\n *<td>medico1</td>", self.decode(response.content))
        self.assertTrue(m)
