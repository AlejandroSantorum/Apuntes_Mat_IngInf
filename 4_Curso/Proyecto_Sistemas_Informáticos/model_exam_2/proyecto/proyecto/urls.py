from django.contrib import admin
from django.urls import path
from django.urls import include
from django.conf import settings
from django.conf.urls.static import static

from aplicacion import views

urlpatterns = [
    path('', views.index, name='landing'),
    path('admin/', admin.site.urls),
    path('aplicacion/', include('aplicacion.urls')),
]
urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)
