var selectedRows = []; // global variable to store selected rows
        window.onload = function() { // when the page loads
            var rows = document.getElementsByTagName("tr"); // get all the rows
            for (var i = 0; i < rows.length; i++) { // for each row
                rows[i].addEventListener("click", function() { // add an event listener to the row
                    var index = selectedRows.indexOf(this); // get the index of the row in the selectedRows array
                    if (this.style.backgroundColor === "lightblue") { // if the row is already selected
                        this.style.backgroundColor = ""; // deselect the row
                        selectedRows.splice(index, 1); // remove the row from the selectedRows array
                    } else { // if the row is not selected
                        this.style.backgroundColor = "lightblue"; // select the row
                        selectedRows.push(this); // add the row to the selectedRows array
                    }
                });
            }
        };

        function hire() { 
        if (selectedRows.length == 1){ // if only one row is selected alert the user that this person is already hired
            alert("This person is already hired.");
        }
        else if(selectedRows.length > 1){ // if more than one row is selected alert the user that these people are already hired
            alert("These people are already hired.");
        } 
        else { // if no rows are selected go to the hire page   
            window.location.href='/hire';
        }
    };

        function fire() { 
            if(selectedRows.length == 0){ // if no rows are selected alert the user to select a person to fire
                alert("Please select a person to fire.");
            }
            else if (selectedRows.length == 1) { // if only one row is selected


                var cells = selectedRows[0].cells;
                var secondLastTd = cells[cells.length - 2];
                var id = secondLastTd.innerText; // get the id of the person
                var jobTitleCell = cells[0];
                var jobTitle = jobTitleCell.innerText; // get the job title of the person
                jobTitle = jobTitle.replace(" ","_"); 

                if (jobTitle.toLowerCase().includes("sale")) { // if the person works in sales alert the user that they cannot be fired
                    alert("This person works in sales. You cannot fire them.");
                }else{ // if the person does not work in sales go to the fire page
                window.location.href='/fire/' + id;
                }
            } else { // if more than one row is selected alert the user that they can only fire one person at a time
                alert("You can only fire one person at a time.");
            }
    };

        function update() { 
        if(selectedRows.length == 0){ // if no rows are selected alert the user to select a person to update
            alert("Please select a person to update.");
        }
        else if(selectedRows.length == 1){ // if only one row is selected go to the update page
            var cells = selectedRows[0].cells;
            var secondLastTd = cells[cells.length - 2];
            var id = secondLastTd.innerText; // get the id of the person
            window.location.href='/update/' + id; 
        }
        else{ // if more than one row is selected alert the user that they can only update one person at a time
            alert("You can only update one person at a time.");
        }
    };