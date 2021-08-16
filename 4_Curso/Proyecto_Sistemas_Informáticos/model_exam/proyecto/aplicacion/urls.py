from django.urls import path
from aplicacion import views

urlpatterns = [
    path('receta', views.receta, name='receta'),
    path('receta/', views.receta, name='receta'),
]
