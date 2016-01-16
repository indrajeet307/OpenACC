import docclass
reload(docclass)

cl = docclass.classifier(docclass.getwords)
docclass.sampledata(cl)
print(cl.weightedprob("money", "good", cl.fprob))


