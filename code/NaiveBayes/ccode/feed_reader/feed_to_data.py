import feedparser
d = feedparser.parse("http://www.thehindu.com/?service=rss")

for feeds in d.entries:
    print("%s\t%s" %(feeds.summary.encode('utf-8'),feeds.tags[0].term.encode('utf-8')))
