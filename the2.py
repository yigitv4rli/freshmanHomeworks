def isCovered(cp_bl, cp_tr, t1_bl, t1_tr, t2_bl, t2_tr):
    x1, y1 = int(cp_bl[0]), int(cp_bl[1])
    x2, y2 = int(cp_tr[0]), int(cp_tr[1])
    
    if int(t1_bl[0]) >= int(t2_bl[0]):    
        x3, y3 = int(t1_bl[0]), int(t1_bl[1])
        x4, y4 = int(t1_tr[0]), int(t1_tr[1])
        x5, y5 = int(t2_bl[0]), int(t2_bl[1])
        x6, y6 = int(t2_tr[0]), int(t2_tr[1])
    else:
        x3, y3 = int(t2_bl[0]), int(t2_bl[1])
        x4, y4 = int(t2_tr[0]), int(t2_tr[1])
        x5, y5 = int(t1_bl[0]), int(t1_bl[1])
        x6, y6 = int(t1_tr[0]), int(t1_tr[1])

    firstArea = (x2-x1) * (y2-y1) 

        
    if (x4 >= x2 and x3 <= x1 and y3 <= y1 and y4 >= y2) or (x5 <= x1 and y5 <= y1 and x6 >= x2 and y6 >= y2):
        return "COMPLETELY COVERED"

    elif y4 >= y2 and y3 <= y1 and x3 <= x2 and x4 >= x2: 
        coveredArea1 = (x2-x3) * (y2-y1)
        if y6 >= y2 and x5 <= x1 and y5 <= y1 and x6 >= x1:
            coveredArea2 = (x6-x1) * (y2-y1)
            if firstArea - (coveredArea1 + coveredArea2) <= 0:
                return "COMPLETELY COVERED"
            else:
                return "NOT COMPLETELY COVERED"
        else:
            return "NOT COMPLETELY COVERED"
    
    elif x3 >= x2:
        if x5 <= x1 and y5 <= y1 and x6 >= x2 and y6 >= y2:
            return "COMPLETELY COVERED"
        else:
            return "NOT COMPLETELY COVERED"

    elif x6 <= x1: 
        if x3 <= x1 and y3 <= y1 and x4 >= x2 and y4 >= y2:
            return "COMPLETELY COVERED"
        else:
            return "NOT COMPLETELY COVERED"

    elif (y3 >= y2 or y4 <= y1) and (y5 >= y2 or y6 <= y1):
        return "NOT COMPLETELY COVERED"

    elif x3 <= x1 and x5 <= x1 and x6 >= x2 and x4 >= x2:
        if (y5 >= y3 and y6 <= y2) and not (y3 < y5 < y6 < y2 or y5 < y3 < y4 < y2):
            coveredArea1 = (y2-y5) * (x2-x1)
            coveredArea2 = (y4-y1) * (x2-x1)
            if firstArea - (coveredArea1 + coveredArea2) <= 0:
                return "COMPLETELY COVERED"
            else:
                return "NOT COMPLETELY COVERED"
        elif (y3 >= y5 and y4 <= y2) and not (y3 < y5 < y6 < y2 or y5 < y3 < y4 < y2):
            coveredArea1 = (y2-y3) * (x2-x1)
            coveredArea2 = (y6-y1) * (x2-x1)
            if firstArea - (coveredArea1 + coveredArea2) <= 0:
                return "COMPLETELY COVERED"
            else:
                return "NOT COMPLETELY COVERED"
        elif (y1 <= y5 <= y2 and y2 >= y4 >= y1 and not (y3 < y5 < y6 < y2 or y5 < y3 < y4 < y2)):
            coveredArea1 = (y2-y5) * (x2-x1)
            coveredArea2 = (y4-y1) * (x2-x1)
            if firstArea - (coveredArea1 + coveredArea2) <= 0:
                return "COMPLETELY COVERED"
            else:
                return "NOT COMPLETELY COVERED"
        elif (y1 <= y3 <= y2 and y2 >= y6 >= y1 and not (y3 < y5 < y6 < y2 or y5 < y3 < y4 < y2)):
            coveredArea1 = (y2-y3) * (x2-x1)
            coveredArea2 = (y6-y1) * (x2-x1)
            if firstArea - (coveredArea1 + coveredArea2) <= 0:
                return "COMPLETELY COVERED"
            else:
                return "NOT COMPLETELY COVERED"
        else:
            return "NOT COMPLETELY COVERED"
    else:
        return "NOT COMPLETELY COVERED"
