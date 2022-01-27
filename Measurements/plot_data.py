import pandas as pd
import plotly.express as px


df = pd.read_csv('./measurements/outputMeasurementSendLightDeep.txt', header=0, names=["Y"])

# uncomment if only part of the data is relevant
# df = df[:217]

# adapt from readings in the plot, to calculate sum of one period
start_period = 0
end_period = 0
# res = sum(df[start_period:end_period)

fig = px.line(df, x = 'X', y = 'Y')
fig.show()
