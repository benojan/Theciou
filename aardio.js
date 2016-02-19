namespace beno {
	import console;
	class Dictionary{
		ctor( /*输入构造函数所需要的参数*/ ){
		
		};
		getDict = function() {
			return this.dict
		}
		print = function() {
			..console.dump(this.dict)
		}
		create = function(filename) {
			this.dict = {}
			this.open(filename)
		};
		open = function(filename) {
			kakxih = ..string.right(filename,4)
			if(kakxih == '.txt') {
				this.openTxtFile(filename)
			}
			elseif(kakxih == '.skk') {
				this.openSkkFile(filename)
			}
		};
		openTxtFile = function(filename) {
			//text = ..string.load(filename)
			for line in ..io.lines(filename) { 
				if(line=='') continue
				var input = ..string.split(line,'\t')
				var zy = input[1]
				var xin = input[2]
				var yvn = input[3]
				var binlih = input[4]
				var diao = input[5]
				var kaxih = input[6]
				this.add(zy,xin,yvn,binlih,diao,kaxih)
			}
		};
		add = function(zy,xin,yvn,binlih,diao,kaxih) {
			if(this.dict[zy]==null) {
				var ins={}
				var i = this.addIn(xin,yvn,binlih,diao,kaxih)
				..table.push(ins,i)
				this.dict[zy]=ins
			}
			else {
				var find_same_xin_yvn = false;
				for k, i in this.dict[zy] {
					//..console.log(..table.tostring(v) )
					if(i.xin == xin and i.yvn == yvn) {
						find_same_xin_yvn = true;
						if(i.diao[diao]==null) {
							kaxihs = ..string.split(kaxih,';');
							i.diao[diao]=kaxihs;
						}
						var find_same_kaxih = false;
						for k, kx in i.diao[diao] {
							if(kx == kaxih) {
					 			find_same_kaxih = true;
					 			break;
					 		}
						}
						if(!find_same_kaxih) {
							..table.push(i.diao[diao], kaxih);
						}
						break;
					}
				}
				if(!find_same_xin_yvn) {
					..table.push(this.dict[zy], this.addIn(xin,yvn,binlih,diao,kaxih))
				}
			}
		};
		addIn = function(xin,yvn,binlih,diao,kaxih) {
			i = {}
			i.xin = xin;
			i.yvn = yvn;
			i.binlih = binlih;
			kaxihs = {}
			if(kaxih!='')
				..table.push(kaxihs, kaxih)
			i.diao = {}
			i.diao[diao] = kaxihs
			return i
		};
	}
	
}
