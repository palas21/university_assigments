function update() {
    // Get the values from the textboxes
    var firstname_textbox = document.getElementById("firstname");
    var middlename_textbox = document.getElementById("middlename");
    var lastname_textbox = document.getElementById("lastname");
    var jobtitle_textbox = document.getElementById("jobtitle");
    var firstname = firstname_textbox.value;
    var middlename = middlename_textbox.value;
    var lastname = lastname_textbox.value;
    var jobtitle = jobtitle_textbox.value;
    var id = document.getElementById("id").placeholder;
    
    // Check if the values are valid
    if(!firstname || firstname == "") {
        firstname = firstname_textbox.placeholder;
    }
    if(!middlename || middlename == "" ) {
        middlename = middlename_textbox.placeholder;
    }
    if(!lastname || lastname == "") {
        lastname = lastname_textbox.placeholder;
    }
    if(!jobtitle || jobtitle == "") {
        jobtitle = jobtitle_textbox.placeholder;
    }
    jobtitle = jobtitle.replaceAll(" ", "_"); // convert jobtitle to the format of the url
    window.location.href='/update/' + id + '/' + firstname + '&' + middlename + '&' + lastname + '&' + jobtitle; // go to the update page 
}