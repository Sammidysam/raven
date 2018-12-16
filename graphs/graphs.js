createData = function (data) {
	// Split our file into lines, removing any blank lines.
	var lines = data.split("\n").filter(function (a) {
		return a != ""
	})

	// Split each line into its attributes (separated by commas).
	var attrs = lines.map(function (a) {
		return a.split(",")
	})

	// Turn each attrs into an object.
	// Basically, we are assigning a variable name to each
	// comma-separated value.
	var objs = attrs.map(function (a) {
		return {
			analysis_date: a[0],
			id: a[1],
			rating: parseInt(a[2]),
			tweet_date: a[3],
			ref_link: a[4]
		}
	})

	// Sort the objs by their tweet date.
	objs.sort(function (a, b) {
		// Turn each string into a date.
		ad = new Date(a.tweet_date)
		bd = new Date(b.tweet_date)

		return ad < bd ? ((bd == ad) ? 0 : -1) : 1
	})

	// Fill in our two main data series:
	// the tweet date of the tweet
	// and the total analysis score
	var total = 0
	var return_data = {
		tweet_dates: [],
		ratings: []
	}

    $.each(objs, function() {
		total += this.rating

        return_data.tweet_dates.push(this.tweet_date)
		return_data.ratings.push(total)
    })

	return return_data
};

createGraph = function (data) {
	// Create the chart.
    var ctx = document.getElementById("canvas").getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: data.tweet_dates,
            datasets: [{
                label: 'Favorability Rating',
                data: data.ratings,
                borderWidth: 1
            }]
        },
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero:true
                    }
                }]
            }
        }
    })
}

// Retrieve our data and process it.
$.get("/James Comey.out", function (data) {
	createGraph(createData(data))
})
