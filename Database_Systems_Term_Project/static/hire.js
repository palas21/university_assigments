function Hire() {

    // get all the values from the form
    var id = document.getElementById('person').value.split(" ")[0];
    var nationalidnumber = document.getElementById("nationalIDNumber").value;
    var jobtitle = document.getElementById("jobtitle").value;
    var birthdate = document.getElementById("birthdate").value;
    var maritalstatus = document.querySelector('input[name="maritalstatus"]:checked').value;
    var gender = document.querySelector('input[name="gender"]:checked').value;
    var hiredate = document.getElementById("hiredate").value;

    // check if the values are valid
    if(!nationalidnumber || nationalidnumber == "" || nationalidnumber.length != 9) {
        alert("National ID Number must be 9 digits long");
        return;
    }

    if(!jobtitle || jobtitle == "") {
        alert("Job Title cannot be empty");
        return;
    }
    if(!birthdate || birthdate == "") {
        alert("Birth Date cannot be empty");
        return;
    }

    // check if the birthdate is valid
    var birthdatedate = new Date(birthdate);
    var today = new Date();
    var eighteenYearsAgo = new Date();
    eighteenYearsAgo.setFullYear(today.getFullYear() - 18);

    var year1930 = new Date();
    year1930.setFullYear(1930);

    if (birthdatedate < year1930 || birthdatedate > eighteenYearsAgo) {
        alert("Birthdate must be between 1930 and 18 years ago.");
        return;
    }

    if(!maritalstatus || maritalstatus == "") {
        alert("Marital Status cannot be empty");
        return;
    }
    if(!gender || gender == ""){
        alert("Gender cannot be empty");
        return;
    }
    if(!hiredate || hiredate == "") {
        alert("Hire Date cannot be empty");
        return;
    }

    jobtitle = jobtitle.replaceAll(" ", "_"); // convert jobtitle to the format of the url
    window.location.href = '/hire/'+ id + '&' + nationalidnumber + '&' + '&' + jobtitle + '&' + birthdate + '&' + maritalstatus + '&' + gender + '&' + hiredate; // go to the hire page
};