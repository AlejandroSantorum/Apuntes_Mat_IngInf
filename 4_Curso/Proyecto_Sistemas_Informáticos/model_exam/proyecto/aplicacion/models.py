from django.db import models


class Paciente(models.Model):
    nombre = models.CharField(max_length=64, blank=False)

    def save(self, *args, **kwargs):
        super(Paciente, self).save(*args, **kwargs)


class Medico(models.Model):
    nombre = models.CharField(max_length=64, blank=False)

    def save(self, *args, **kwargs):
        super(Medico, self).save(*args, **kwargs)


class Receta(models.Model):
    medico = models.ForeignKey(Medico, on_delete=models.CASCADE, blank=False,
                                       related_name="medico_receta")
    paciente = models.ForeignKey(Paciente, on_delete=models.CASCADE, blank=False,
                                       related_name="paciente_receta")

    def save(self, *args, **kwargs):
        super(Receta, self).save(*args, **kwargs)
