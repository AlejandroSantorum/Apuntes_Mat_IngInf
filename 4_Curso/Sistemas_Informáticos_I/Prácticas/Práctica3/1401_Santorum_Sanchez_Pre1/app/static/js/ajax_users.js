$(document).ready(function () {
    function getUsers(){
        $.ajax({
            type: 'GET',
            url: "./connectedusers",
            success:
                function(data){
                    data = 'Usuarios: ' + data;
                    $('#users').html(data);
                },
            complete:
                function(){
                    setTimeout(getUsers, 3000);
                }
            });
    };

    setTimeout(getUsers, 0);
});
