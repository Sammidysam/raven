FILE = <path to file>
x_data <- read.csv(FILE,header=FALSE)
vars = c("V3","V1")
sub_data=x_data[vars]
plot(sub_data,xlab="Rating",ylab="Creation Time",main= "")

