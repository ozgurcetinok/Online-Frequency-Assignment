setwd("~/Desktop/IE 492")
data<-read.csv("492.csv",header =T,skip=12)
data <- data[1:which(data$who == "PATCHES")-1,]


data <- data[,c("xcor","ycor","starttime","finishtime")]

data$xcor <- as.numeric(as.character(data$xcor))
data$ycor <- as.numeric(as.character(data$ycor))
data$starttime <- as.numeric(as.character(data$starttime))
data$finishtime <- as.numeric(as.character(data$finishtime))

neighbor<-matrix(0,nrow = nrow(data),ncol = nrow(data))

#call numaralari normalde 0'dan basliyor, burda 1'den basliyor sonra -1.
for(i in 1:nrow(data)){
  for(j in i:nrow(data)){
    if(data[i,"finishtime"]>=data[j,"starttime"]){
      if(sqrt((data[i,"xcor"]-data[j,"xcor"])*
              (data[i,"xcor"]-data[j,"xcor"])+(data[i,"ycor"]-data[j,"ycor"])*(data[i,"ycor"]-data[j,"ycor"]))<=5){
        neighbor[i,j]<-1
      }
    }
  }
} 

#arcset <- matrix(0,nrow=1,ncol=2)
#for(i in 1:nrow(data))
#{
#  for (j in 1:nrow(data))
#  {
#    if(neighbor[i,j]==1 & i != j)
#      arcset<-rbind(arcset,c(i,j))
#  }
#}
#arcset <- arcset[-1,]


diag(neighbor)<-0

write.table(neighbor,"neighbor.txt",sep=",",row.names=F,col.names=F)
#write.table(arcset, "arcset.txt",sep=",",row.names=F,col.names=F)
