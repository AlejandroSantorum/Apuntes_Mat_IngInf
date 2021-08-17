function initListener(){
$(document).find('textarea').keyup(function(evt) { 
		if ($(evt.target).siblings('.textCount')) {
		var characters = $(evt.target).val().length;
		$(evt.target).siblings('.textCount').text(characters + ' characters');
		}
});

}
