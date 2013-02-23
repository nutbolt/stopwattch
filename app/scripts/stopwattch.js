function fetchData() {
    $.ajax({
            type:'get', 
            dataType: "json", 
            url:'json.txt',
            success: function(data) {
                $.plot($("#graph"), [data], { xaxis: { mode: "time" } } );
            }
        });
   //setTimeout(fetchData, 100); //enable for auto-updating
};

fetchData();