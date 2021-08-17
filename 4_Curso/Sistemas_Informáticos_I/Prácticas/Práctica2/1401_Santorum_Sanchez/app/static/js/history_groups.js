$(document).ready( function() {
    $("input[class^=history-button]").on('click', function () {
        var button = $(this);
        var value = button.val();
        var id = button.attr('id').substring('button-'.length);
        var tbody = $('#body-'+id)

        if (value === 'Ocultar'){
            button.val('Mostrar');
            tbody.children('.history-product-info').addClass('collapse');
        }else{
            button.val('Ocultar');
            tbody.children('.history-product-info').removeClass('collapse');
        }
    });
});
